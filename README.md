# Il2CppModFramework
## A framework for creating mods for Unity games built with il2cpp. Focused on performance.
## &#x26A0;&#xFE0F; UNSTABLE / UNDER DEVELOPMENT &#x26A0;&#xFE0F;

# Contents
- [Initial configuration](#initial-configuration)
  - [Recomended file structure](#recomended-file-structure)
  - [Create root for mods](#create-root-for-mods)
  - [Clone repo and submodules](#clone-repo-and-submodules)
- [Creating new mod](#creating-new-mod)
  - [Folowing an example](#folowing-an-example)
  - [Creating new module](#creating-new-module)
  - [Creating new logger](#creating-new-logger)
- [CMake settings](#cmake-settings)
  - [Full list of options](#full-list-of-options)

# Initial configuration

## Install tools and dependencies
- Visual Studio [link](https://visualstudio.microsoft.com/downloads/)
- cmake [link](https://cmake.org/download/)
- git [link](https://git-scm.com/install/windows)

## Recomended file structure
```
icmf_mods
|- my-mod1
|  |- CMakeLists.txt
|
|- my-mod2
|  |- CMakeLists.txt
|
|- Il2CppModFramework
   |- CMakeLists.txt
```

## Create root for mods
```sh
mkdir icmf_mods
cd icmf_mods
```

## Clone repo and submodules
```sh
git clone https://github.com/kerrytazi/Il2CppModFramework.git
git -C Il2CppModFramework submodule update --init --filter=blob:none
```
**NOTE**: `--filter=blob:none` is used because we don't need whole history for libraries, which would otherwise download and use ~500MB of extra storage.

# Creating new mod

## Folowing an example

Copy `example` mod:
```sh
cp Il2CppModFramework/example my-mod
```

Navigate to it:
```sh
cd my-mod
```

*(Optional)* Init version control:
```sh
git init
```

Edit `CMakeLists.txt`:
- `project("my-mod")`
- `set(ICMF_UNITY_VERSION 2021.3.56f2)`
- `config_client(my-mod)`

Edit `src/framework_config.cpp`:
- `GetConfigPath` - relative path *(from exe)* to mod settings.
- `GetUnityGameWindow` - expected game window *(HWND)*.
- `GetImGuiIniFilename` - relative path *(from exe)* to imgui settings.
- `GetImGuiLogFilename` - relative path *(from exe)* to imgui logs.

You can remove these functions. The framework will fallback to default settings.

Configure `cmake`:
```sh
cmake -B build
```

## Creating new module

In `modules` folder *(or anywhere else inside `my-mod` folder)* you can implement modules of your mod.

Each Module must inherit from `Module` class and should be registered using `RegisterModuleStatic` to work properly.

**Note**: You can set the loading order priority using the second template argument of `RegisterModuleStatic`.
Modules will `Unload` in reverse order. The first to `Load` is the last to `Unload`.

Module can override any of:
- `virtual void Load()` - Called once module load.
- `virtual void Unload()` - Called once module unload.
- `virtual void PreUpdate()` - Called each frame *before* any other `MonoBehaviour`'s `Update`.
- `virtual void Update()` - Called each frame.
- `virtual void PostUpdate()` - Called each frame *after* any other `MonoBehaviour`'s `Update`.
- `virtual void SaveConfig(nlohmann::json& doc)` - Called when the framework wants to save user settings *(usually before `Unload`)*.
- `virtual void LoadConfig(const nlohmann::json& doc)` - Called when the framework wants to load user settings *(usually after `Load`)*.
- `virtual bool IsForceImGui()` - Return true if you want to render ImGui even if main menu is closed.
- `virtual void OnImGuiMenu()` - Called each frame when main menu visible. You should not create any new ImGui windows here.
- `virtual void OnPostImGuiMenu()` - Called each frame. You can create other ImGui windows here. Or render custom *onscreen* primitives.

**NOTE**: All functions are called on main thread.

**NOTE**: You can't use `UnityEngine::Input::GetKey` or similar input related functions in `PostUpdate`.

## Creating new logger

In the `loggers` folder *(or anywhere else inside `my-mod` folder)* you can implement custom loggers.
These are called each time you call any function from the `Log` namespace.

Each Logger must be inherited from `Logger`. And should be registered using `RegisterLoggerStatic` to work properly.

**NOTE**: You can set log order priority using `RegisterLoggerStatic` second template argument.

Logger can override any of:
- `virtual void AddLine(Level level, Type type, std::initializer_list<cs::StyledString> line)` - Called each time you call any function from the `Log` namespace.
- `virtual void Flush()` - Flush any cached info. Usually called after `Unload` or during crash handler.
It's up to you to filter messages by their `level` and `type`.


# CMake settings
You can set additional options before add_subdirectory(Il2CppModFramework ...

## Full list of options
|Name|Description|Possible values. [Default]|
|-|-|-|
|`ICMF_ENABLE_IMGUI`|Enable ImGui|`[ON]/OFF`|
|`ICMF_LOADER`|Loader type|`[DLL_INJECTOR]/MANUAL_MAPPER`|
|`ICMF_STACK_TRACER`|Stack Tracer implementation|`[DBGHELP]/DIA/NONE`|

