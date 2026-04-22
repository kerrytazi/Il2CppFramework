#include "Il2CppModFramework/WindowsWrapper.hpp"

void _BootstrapInit();
void _BootstrapDeinit();

static HMODULE g_dll_module = nullptr;

static DWORD WINAPI _UnloadViaThreadFunc(void* param)
{
	(void)param;

	Sleep(100);
	FreeLibraryAndExitThread(g_dll_module, 0);
}

void _UnloadViaThread()
{
	CreateThread(nullptr, 0, &_UnloadViaThreadFunc, nullptr, 0, nullptr);
}

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	(void)lpvReserved;

	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			g_dll_module = hinstDLL;
			_BootstrapInit();
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
			_BootstrapDeinit();
			break;
	}

	return TRUE;
}
