#include "Il2CppModFramework/Mod.hpp"
#include "Il2CppModFramework/WindowsWrapper.hpp"

#include "$il2cpp/Base.hpp"

#include "DetourLambda/DetourLambda.hpp"

#include <optional>
#include <stdexcept>
#include <ranges>

static std::optional<DetourLambda<int64_t()>> g_player_loop_detour;
static std::atomic<bool> g_loaded = false;
static std::atomic<bool> g_request_unload = false;

void _UnloadViaThread();

static void PatchPlayerLoop(int64_t(*update_func)())
{
	g_player_loop_detour.emplace(update_func, [](auto original) -> int64_t {
		if (bool check = false; g_loaded.compare_exchange_strong(check, true)) [[unlikely]]
		{
			ModOnLoad();
		}

		ModOnUpdate();
		auto result = original();
		ModOnPostUpdate();

		if (bool check = true; g_request_unload.compare_exchange_strong(check, false)) [[unlikely]]
		{
			ModOnUnload();
			_UnloadViaThread();
		}

		return result;
	});
}

static bool PatchUnityPlayerLoop()
{
	const uint8_t err_message[] =
		"An abnormal situation has occurred: "
		"the PlayerLoop internal function has been called recursively. "
		"Please contact Customer Support with a sample project "
		"so that we can reproduce the problem and troubleshoot it.";

	auto UnityPlayerMem = GetModuleMemory((HMODULE)$il2cpp::UnityPlayerBase);

	auto found_message = std::ranges::search(UnityPlayerMem, err_message);

	if (found_message.empty())
		return false;

	const uint8_t* err_message_begin = &*found_message.begin();
	const uint8_t* lea_err_message = nullptr;

	for (auto& it : UnityPlayerMem)
	{
		// 48 8D 05 <immediate>   lea rax, [err_message_begin]
		int immediate = int(err_message_begin - &it) - 4;

		if (memcmp(&it, &immediate, 4) == 0)
		{
			lea_err_message = &it;
			break;
		}
	}

	if (lea_err_message == nullptr)
		return false;

	auto find_instruction_up = [&](std::initializer_list<uint8_t> instr) -> const uint8_t* {
		for (const uint8_t* it = lea_err_message; it != lea_err_message - 1024; --it)
			if (memcmp(it, instr.begin(), instr.size()) == 0)
				return it;

		return nullptr;
	};

	// 40 55   push rbp
	auto push_rbp = find_instruction_up({ 0x40, 0x55 });

	// 48 83 EC XX  sub rsp, <imm>
	auto sub_rsp = find_instruction_up({ 0x48, 0x83, 0xEC });

	auto func_start = (sub_rsp < push_rbp) ? push_rbp : sub_rsp;

	PatchPlayerLoop((int64_t(*)())func_start);

	return true;
}





void FrameworkRequestUnload()
{
	g_request_unload = true;
}

void _BootstrapInit()
{
	ModBeforeBootstrapInit();
	$il2cpp::InitializeIl2Cpp();
	PatchUnityPlayerLoop();
}

void _BootstrapDeinit()
{
	ModAfterBootstrapDeinit();
}
