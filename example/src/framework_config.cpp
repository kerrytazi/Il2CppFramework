#include "pch.hpp"

#include "common/ModuleManager.hpp"
#include "common/MyWindows.hpp"

// Optional. You can remove this function.
// Will fallback to DefaultGetConfigPath.
// If you want to disable config saving then return nullptr.
extern "C" const char* GetConfigPath()
{
	return "client/config.json";
}

// Optional. You can remove this function.
// Will fallback to DefaultGetUnityGameWindow.
extern "C" HWND GetUnityGameWindow()
{
	return FindWindowA(nullptr, "TestGame");
}

#ifdef ICMF_ENABLE_IMGUI
// Optional. You can remove this function.
// Will fallback to DefaultOnImGuiInit.
// You can set up fonts/styles here.
extern "C" void OnImGuiInit()
{
	auto& io = ImGui::GetIO();

	if (!io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/segoeui.ttf", 22.0f))
		io.Fonts->AddFontDefault();

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
}

// Optional. You can remove this function.
// Will fallback to DefaultGetImGuiIniFilename.
// If you want to disable imgui saving then return nullptr.
extern "C" const char* GetImGuiIniFilename()
{
	return "client/imgui.ini";
}

// Optional. You can remove this function.
// Will fallback to DefaultGetImGuiLogFilename.
// If you want to disable imgui logs then return nullptr.
extern "C" const char* GetImGuiLogFilename()
{
	return "client/imgui.log";
}

// Optional. You can remove this function.
// Will fallback to DefaultGetImGuiSwitchClientMenuKey.
extern "C" int GetImGuiSwitchClientMenuKey()
{
	return VK_INSERT;
}
#endif // ICMF_ENABLE_IMGUI
