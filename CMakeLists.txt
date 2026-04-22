cmake_minimum_required(VERSION 4.3)
project("Il2CppModFramework" LANGUAGES CXX)

include(FetchContent)

include(cmake/check_file_changed.cmake)
include(cmake/config_all_projects.cmake)
include(cmake/config_project.cmake)
include(cmake/config_mod.cmake)

add_library(Il2CppModFramework STATIC)

target_sources(Il2CppModFramework PRIVATE
	cmake/check_file_changed.cmake
	cmake/config_all_projects.cmake
	cmake/config_project.cmake
	cmake/config_mod.cmake

	src/bootstrap/bootstrap_common.cpp
	src/DefaultMod.cpp
	src/WindowsWrapper.cpp

	include/Il2CppModFramework/Mod.hpp
	include/Il2CppModFramework/WindowsWrapper.hpp
)

target_include_directories(Il2CppModFramework
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

config_all_projects()
config_project(Il2CppModFramework)

target_precompile_headers(Il2CppModFramework
	PRIVATE
		include/Il2CppModFramework/WindowsWrapper.hpp
		<span>
		<string>
		<stdexcept>
)


add_subdirectory(libs/DetourLambda)
target_link_libraries(Il2CppModFramework PUBLIC DetourLambda)






if(NOT DEFINED Il2CppDumper_Params_Output)
	set(Il2CppDumper_Params_Output "${CMAKE_CURRENT_BINARY_DIR}/DumperOutput")
endif()

set(Il2CppDumper_Params "--create-cpp-project" "--output" "${Il2CppDumper_Params_Output}")

if(DEFINED Il2CppDumper_Params_GameAssembly)
	set(Il2CppDumper_Params ${Il2CppDumper_Params} "--game-assembly" "${Il2CppDumper_Params_GameAssembly}")
else()
	message(FATAL_ERROR "Must set Il2CppDumper_Params_GameAssembly before Il2CppModFramework")
endif()

if(DEFINED Il2CppDumper_Params_MetadataPath)
	set(Il2CppDumper_Params ${Il2CppDumper_Params} "--metadata-path" "${Il2CppDumper_Params_MetadataPath}")
endif()

if(Il2CppDumper_Params_CreateCSDump)
	set(Il2CppDumper_Params ${Il2CppDumper_Params} "--create-cs-dump")
endif()

if(Il2CppDumper_Params_Normalize)
	set(Il2CppDumper_Params ${Il2CppDumper_Params} "--normalize")
endif()

set(Il2CppDumper_Execute_Generate "${CMAKE_COMMAND}" -B "${CMAKE_CURRENT_BINARY_DIR}/Il2CppRuntimeDumper" -S "${CMAKE_CURRENT_SOURCE_DIR}/libs/Il2CppRuntimeDumper")

if(DEFINED Il2CppDumper_Params_Plugin)
	set(Il2CppDumper_Execute_Generate ${Il2CppDumper_Execute_Generate} "-DIl2CppRuntimeDumper_EXTRA_SOURCES=${Il2CppDumper_Params_Plugin}")
endif()

if(NOT DEFINED Il2CppDumper_Params_Config)
	set(Il2CppDumper_Params_Config Release)
endif()

string(REPLACE ";" " " tmp_msg "${Il2CppDumper_Execute_Generate}")
message(STATUS ${tmp_msg})
execute_process(
	COMMAND ${Il2CppDumper_Execute_Generate}
	COMMAND_ERROR_IS_FATAL ANY
)

include_external_msproject(Il2CppRuntimeDumper "${CMAKE_CURRENT_BINARY_DIR}/Il2CppRuntimeDumper/Il2CppRuntimeDumper.vcxproj")

set(Il2CppDumper_Execute_Build "${CMAKE_COMMAND}" "--build" "${CMAKE_CURRENT_BINARY_DIR}/Il2CppRuntimeDumper" "--config" ${Il2CppDumper_Params_Config})

string(REPLACE ";" " " tmp_msg "${Il2CppDumper_Execute_Build}")
message(STATUS ${tmp_msg})
execute_process(
	COMMAND ${Il2CppDumper_Execute_Build}
	COMMAND_ERROR_IS_FATAL ANY
)

check_file_changed(GameAssembly_CHANGED ${Il2CppDumper_Params_GameAssembly} GameAssemblyCheck)
check_file_changed(Il2CppRuntimeDumper_CHANGED "${CMAKE_CURRENT_BINARY_DIR}/Il2CppRuntimeDumper/${Il2CppDumper_Params_Config}/Il2CppRuntimeDumper.exe" Il2CppRuntimeDumperCheck)

if(GameAssembly_CHANGED OR Il2CppRuntimeDumper_CHANGED)
	set(Il2CppDumper_Execute_Run "${CMAKE_CURRENT_BINARY_DIR}/Il2CppRuntimeDumper/${Il2CppDumper_Params_Config}/Il2CppRuntimeDumper.exe" ${Il2CppDumper_Params})
	string(REPLACE ";" " " tmp_msg "${Il2CppDumper_Execute_Run}")
	message(STATUS ${tmp_msg})
	execute_process(
		COMMAND ${Il2CppDumper_Execute_Run}
		COMMAND_ERROR_IS_FATAL ANY
	)
endif()

add_subdirectory("${Il2CppDumper_Params_Output}/cpp" GameAssembly)

target_link_libraries(Il2CppModFramework PUBLIC GameAssembly)
