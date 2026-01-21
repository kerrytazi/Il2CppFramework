#include "pch.hpp"

#include "StackTracer/StackTracer.hpp"

#include "common/Log.hpp"

#include "common/MyWindows.hpp"

#include <sstream>
#include <optional>
#include <dbghelp.h>
#include <mutex>

#pragma comment(lib, "dbghelp.lib")

struct Initializer
{
	std::optional<bool> initialized;
	HANDLE for_process = nullptr;

	~Initializer()
	{
		CleanupSymbols();
	}

	bool InitSymbols(HANDLE process)
	{
		if (!initialized.has_value())
		{
			SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);

			if (SymInitialize(process, nullptr, TRUE))
			{
				initialized = true;
				for_process = process;
			}
			else
			{
				Log::Error("SymInitialize failed: ", GetLastError());
				initialized = false;
			}
		}

		return *initialized;
	}

	void CleanupSymbols()
	{
		if (for_process)
		{
			initialized = std::nullopt;
			SymCleanup(for_process);
		}
	}
};

static Initializer g_symbols_initializer;
static std::mutex g_mtx;

struct StackFrame
{
	DWORD64 address;
	std::string name;
	std::string module;
	DWORD line_number;
	std::string file_name;
};

static std::vector<StackFrame> WalkStack(HANDLE process, HANDLE thread, const CONTEXT* context)
{
	std::vector<StackFrame> frames;

	// Initialize stack frame based on architecture
#ifdef _M_IX86
	STACKFRAME stack_frame{};
	DWORD machine_type = IMAGE_FILE_MACHINE_I386;
	stack_frame.AddrPC.Offset = context->Eip;
	stack_frame.AddrPC.Mode = AddrModeFlat;
	stack_frame.AddrFrame.Offset = context->Ebp;
	stack_frame.AddrFrame.Mode = AddrModeFlat;
	stack_frame.AddrStack.Offset = context->Esp;
	stack_frame.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
	STACKFRAME64 stack_frame{};
	DWORD machine_type = IMAGE_FILE_MACHINE_AMD64;
	stack_frame.AddrPC.Offset = context->Rip;
	stack_frame.AddrPC.Mode = AddrModeFlat;
	stack_frame.AddrFrame.Offset = context->Rbp;
	stack_frame.AddrFrame.Mode = AddrModeFlat;
	stack_frame.AddrStack.Offset = context->Rsp;
	stack_frame.AddrStack.Mode = AddrModeFlat;
#else
	#error Unsupported architecture
#endif

	for (int frame_num = 0; frame_num < 128; frame_num++)
	{
		if (!StackWalk64(
			machine_type,
			process,
			thread,
			&stack_frame,
			(void*)context,
			nullptr,
			&SymFunctionTableAccess64,
			&SymGetModuleBase64,
			nullptr))
		{
			break;
		}

		if (stack_frame.AddrPC.Offset == 0)
			break;

		StackFrame frame{};
		frame.address = stack_frame.AddrPC.Offset;

		// Try to get symbol name
		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
		PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;

		DWORD64 displacement = 0;
		if (SymFromAddr(process, stack_frame.AddrPC.Offset, &displacement, symbol))
		{
			frame.name = symbol->Name;
		}
		else
		{
			frame.name = "<unknown>";
		}

		IMAGEHLP_LINE64 line = {};
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		DWORD line_displacement = 0;

		if (SymGetLineFromAddr64(process, stack_frame.AddrPC.Offset, &line_displacement, &line))
		{
			frame.line_number = line.LineNumber;
			frame.file_name = line.FileName;
		}

		// Get module name
		IMAGEHLP_MODULE64 module_info = {};
		module_info.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
		if (SymGetModuleInfo64(process, stack_frame.AddrPC.Offset, &module_info))
		{
			frame.module = module_info.ModuleName;
		}

		frames.push_back(frame);
	}

	return frames;
}

static void LogFrames(const std::vector<StackFrame>& frames)
{
	Log::Error(cs::Red("Stack Trace ("), cs::Red(frames.size()), cs::Red(" frames):"));
	for (size_t i = 0; i < frames.size(); ++i)
	{
		const auto& frame = frames[i];
		bool n = !frame.file_name.empty();
		bool m = !frame.module.empty();

		Log::Error(
			cs::Green(Log::Pad(i, ' ', 2)), cs::Red(": "), cs::Red(frame.name), cs::Red(" ["), cs::Cyan("0x"), cs::Cyan((void*)frame.address), cs::Red("]"),
			cs::Red(n ? " at " : ""), cs::Yellow(n ? frame.file_name : ""), cs::Red(n ? ":" : ""), cs::Red(n ? su::u8(frame.line_number) : ""),
			cs::Red(m ? " (" : ""), cs::Yellow(m ? frame.module : ""), cs::Red(m ? ")" : "")
		);
	}
}

static std::string FormatFrames(const std::vector<StackFrame>& frames)
{
	std::stringstream ss;

	ss << "Stack Trace (" << frames.size() << " frames):\n";
	for (size_t i = 0; i < frames.size(); ++i)
	{
		const auto& frame = frames[i];
		ss << i << ": " << frame.name
			<< " [0x" << std::hex << frame.address << std::dec << "]";

		if (!frame.file_name.empty())
		{
			ss << " at " << frame.file_name << ":" << frame.line_number;
		}

		if (!frame.module.empty())
		{
			ss << " (" << frame.module << ")";
		}

		if (i != frames.size() - 1)
			ss << "\n";
	}

	return std::move(ss).str();
}

std::string StackTracer::GetStackTrace()
{
	std::unique_lock lock(g_mtx);

	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();

	if (g_symbols_initializer.InitSymbols(process))
	{
		CONTEXT context{};
		context.ContextFlags = CONTEXT_FULL;
		RtlCaptureContext(&context);

		auto frames = WalkStack(process, thread, &context);
		return FormatFrames(frames);
	}
	else
	{
		return "StackTracer::GetStackTrace() failed. Can't InitSymbols";
	}
}

std::string StackTracer::GetStackTrace(_EXCEPTION_POINTERS* pointers)
{
	std::unique_lock lock(g_mtx);

	if (!pointers)
		return "StackTracer::GetStackTrace(pointers) failed. pointers == null";

	if (!pointers->ContextRecord)
		return "StackTracer::GetStackTrace(pointers) failed. pointers->ContextRecord == null";

	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();

	if (g_symbols_initializer.InitSymbols(process))
	{
		auto frames = WalkStack(process, thread, pointers->ContextRecord);
		return FormatFrames(frames);
	}
	else
	{
		return "StackTracer::GetStackTrace(pointers) failed. Can't InitSymbols";
	}
}

void StackTracer::LogStackTrace()
{
	std::unique_lock lock(g_mtx);

	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();

	if (g_symbols_initializer.InitSymbols(process))
	{
		CONTEXT context{};
		context.ContextFlags = CONTEXT_FULL;
		RtlCaptureContext(&context);

		auto frames = WalkStack(process, thread, &context);
		LogFrames(frames);
	}
	else
	{
		Log::Error(cs::Red("StackTracer::LogStackTrace() failed. Can't InitSymbols"));
	}
}

int StackTracer::LogStackTrace(_EXCEPTION_POINTERS* pointers)
{
	std::unique_lock lock(g_mtx);

	if (!pointers)
	{
		Log::Error(cs::Red("StackTracer::LogStackTrace(pointers) failed. pointers == null"));
		return 0;
	}

	if (!pointers->ContextRecord)
	{
		Log::Error(cs::Red("StackTracer::LogStackTrace(pointers) failed. pointers->ContextRecord == null"));
		return 0;
	}

	HANDLE process = GetCurrentProcess();
	HANDLE thread = GetCurrentThread();

	if (g_symbols_initializer.InitSymbols(process))
	{
		auto frames = WalkStack(process, thread, pointers->ContextRecord);

		if (frames.empty())
		{
			Log::Error(cs::Red("StackTracer::LogStackTrace(pointers) failed. Zero frames found"));
			return 0;
		}

		LogFrames(frames);
		return (int)frames.size();
	}
	else
	{
		Log::Error(cs::Red("StackTracer::LogStackTrace(pointers) failed. Can't InitSymbols"));
	}

	return 0;
}
