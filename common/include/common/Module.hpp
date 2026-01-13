#pragma once

#include "nlohmann/json.hpp"

// Interface for your module.
// All functions are called on main thread.
class Module
{
public:

	virtual ~Module();

	// Called once module load.
	virtual void Load();

	// Called once module unload.
	virtual void Unload();

	// Called each frame *before* any other MonoBehaviour's Update.
	virtual void PreUpdate();

	// Called each frame.
	virtual void Update();

	// Called each frame *after* any other MonoBehaviour's Update.
	// NOTE: You can't use UnityEngine::Input::GetKey or similar input related functions in PostUpdate.
	virtual void PostUpdate();

	// Called when the framework wants to save user settings *(usually before Unload).
	virtual void SaveConfig(nlohmann::json& doc);

	// Called when the framework wants to load user settings (usually after Load).
	virtual void LoadConfig(const nlohmann::json& doc);

#ifdef UC_ENABLE_IMGUI
	// Return true if you want to render ImGui even if main menu is closed.
	virtual bool IsForceImGui();

	// Called each frame when main menu visible.
	// You should not create any new ImGui windows here.
	virtual void OnImGuiMenu();

	// Called each frame. You can create other ImGui windows here.
	// Or render custom onscreen primitives.
	virtual void OnPostImGuiMenu();
#endif // UC_ENABLE_IMGUI

	// Requires NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT
	// and TConfig::mod_name to be declared for TConfig.
	template <typename TConfig>
	void SimpleSaveConfig(nlohmann::json& doc, const TConfig& config)
	{
		doc[TConfig::mod_name] = config;
	}

	// Requires NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT
	// and TConfig::mod_name to be declared for TConfig.
	// Returns found json object if exists.
	template <typename TConfig>
	const nlohmann::json* SimpleLoadConfig(const nlohmann::json& doc, TConfig& config)
	{
		auto mod = doc.find(TConfig::mod_name);

		if (mod != doc.end() && mod->is_object())
		{
			config = mod->get<TConfig>();
			return &*mod;
		}

		return nullptr;
	}
};
