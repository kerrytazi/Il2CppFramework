#include "pch.hpp"

#include "common/ModuleManager.hpp"
#include "common/Module.hpp"

#include "common/StringUtils.hpp"
#include "common/Log.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Component.hpp"
#include "System/Exception.hpp"
#include "System/String.hpp"
#include "il2cpp/il2cpp.hpp"
#include "il2cpp/Class.hpp"

#include "StackTracer/StackTracer.hpp"

class TestModule : public Module
{
public:

	virtual void Load() override
	{
		Log::Info("TestModule loaded");
	}

private:

	void TestLog()
	{
		Log::Debug(Logger::Type::System, "Hello ", 3, " world ", cs::Default(false), " ", true);
		Log::Info(u"Hello ", 3, u" world ", cs::Default(false), " ", true);
		Log::Warn((const void*)"Hello", " ", (void*)"world");
		Log::Error(Log::Pad(123), " ", Log::Hex(123), " ", Log::Pad(Log::Hex(123)));
		Log::Error(su::u8((void*)"hello"));
	}

	void TestStackTracer()
	{
		auto traces_str = StackTracer::GetStackTrace();
		auto traces = su::SplitView<char>(traces_str, "\n");

		for (const auto& trace : traces)
			Log::Debug(trace);
	}

	void TestException()
	{
		using func_t = int(*)(void*);
		func_t func = (func_t)(il2cpp::GetGameAssemblyBase() + 0x6F17C20); // FIXME

		try
		{
			func(nullptr);
		}
		catch (const std::exception& ex)
		{
			Log::Debug("Exception: ", ex.what());
		}
		catch (Il2CppExceptionWrapper& ex)
		{
			Log::Debug("Exception: ", ex.GetException()->GetMessage()->AsU16StringView());
			Log::Debug("Exception: ", ex.GetException()->GetSource()->AsU16StringView());
			Log::Debug("Exception: ", ex.GetException()->GetStackTrace()->AsU16StringView());
			Log::Debug("Exception: ", ex.GetException()->GetInnerException());
		}
		catch (...)
		{
			Log::Debug("Exception ?");
		}
	}
};

static RegisterModuleStatic<TestModule> registered;
