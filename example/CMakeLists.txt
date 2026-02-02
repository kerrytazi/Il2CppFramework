cmake_minimum_required(VERSION 3.13)
project("example_mod")

# You can find this version in .exe -> Properties -> Details -> Product version
set(ICMF_UNITY_VERSION 2021.3.56f2)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/.." "Il2CppModFramework")

config_mod(example_mod)

# Add pch to speed up compilation of mod
target_precompile_headers(example_mod PRIVATE src/pch.hpp)

# To make includes from src easier
target_include_directories(example_mod PRIVATE "src")

# Set our mod as startup project.
# So we can simply Ctrl+Shift+B to build it
set_property(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}" PROPERTY VS_STARTUP_PROJECT example_mod)

set_target_properties(example_mod PROPERTIES
	VS_DEBUGGER_COMMAND "$<TARGET_FILE:dll_injector>"
	VS_DEBUGGER_COMMAND_ARGUMENTS "--target-name VRChat.exe --dll-name $<TARGET_FILE:example_mod>"
	VS_DEBUGGER_ATTACH "false"
)

# Uncomment if you want automatic unity type generation for game classes/structs
#add_autogen(example_mod)
#target_include_directories(example_mod_autogen PRIVATE "src")
