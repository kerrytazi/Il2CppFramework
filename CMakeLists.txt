cmake_minimum_required(VERSION 3.13)
project("Il2CppModFramework")

set(ICMF_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(ICMF_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}" PARENT_SCOPE)
set(CMAKE_CXX_STANDARD 20)

include("${ICMF_SOURCE_DIR}/cmake/config_flags.cmake")
include("${ICMF_SOURCE_DIR}/cmake/config_mod.cmake")
include("${ICMF_SOURCE_DIR}/cmake/version_to_number.cmake")

if(NOT DEFINED ICMF_UNITY_VERSION)
	message(FATAL_ERROR "ICMF_UNITY_VERSION is not defined")
endif()

version_to_number("${ICMF_UNITY_VERSION}" ICMF_UNITY_VERSION_NUM)
message(STATUS "ICMF_UNITY_VERSION:     ${ICMF_UNITY_VERSION}")
message(STATUS "ICMF_UNITY_VERSION_NUM: ${ICMF_UNITY_VERSION_NUM}")
set(ICMF_UNITY_VERSION_NUM ${ICMF_UNITY_VERSION_NUM} PARENT_SCOPE)

message(STATUS "ICMF_SOURCE_DIR ${ICMF_SOURCE_DIR}")

option(ICMF_ENABLE_IMGUI "Enable ImGui" ON)
message(STATUS "ICMF_ENABLE_IMGUI ${ICMF_ENABLE_IMGUI}")

set(ICMF_LOADER "DLL_INJECTOR" CACHE STRING "Loader type")
message(STATUS "ICMF_LOADER ${ICMF_LOADER}")

set(ICMF_STACK_TRACER "DBGHELP" CACHE STRING "Stack Tracer implementation")
message(STATUS "ICMF_STACK_TRACER ${ICMF_STACK_TRACER}")

#print_all_flags()
reset_all_flags()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(Il2CppModFramework INTERFACE)
set_property(TARGET Il2CppModFramework PROPERTY FOLDER "Il2CppModFramework")

add_library(cmake INTERFACE
	CMakeLists.txt
	cmake/add_autogen.cmake
	cmake/add_optimized.cmake
	cmake/config_common.cmake
	cmake/config_flags.cmake
	cmake/config_mini.cmake
	cmake/config_mod.cmake
	cmake/create_source_filters.cmake
	cmake/find_dia_sdk.cmake
	cmake/version_to_number.cmake
)
add_dependencies(Il2CppModFramework cmake)
set_property(TARGET cmake PROPERTY FOLDER "Il2CppModFramework")

if(ICMF_LOADER STREQUAL "DLL_INJECTOR")
	add_subdirectory("${ICMF_SOURCE_DIR}/loaders/dll_injector" "loaders/dll_injector" EXCLUDE_FROM_ALL)
	add_dependencies(Il2CppModFramework dll_injector)
	set_property(TARGET dll_injector PROPERTY FOLDER "Il2CppModFramework/loaders")
endif()

add_subdirectory("${ICMF_SOURCE_DIR}/tools/autogen" "tools/autogen" EXCLUDE_FROM_ALL)
add_dependencies(Il2CppModFramework autogen)
set_property(TARGET autogen PROPERTY FOLDER "Il2CppModFramework/tools")

add_subdirectory("${ICMF_SOURCE_DIR}/common" "common" EXCLUDE_FROM_ALL)
target_link_libraries(Il2CppModFramework INTERFACE common)
set_property(TARGET common PROPERTY FOLDER "Il2CppModFramework")
set_property(TARGET common_optimized PROPERTY FOLDER "Il2CppModFramework")

add_subdirectory("${ICMF_SOURCE_DIR}/debuggers/StackTracer" "debuggers/StackTracer" EXCLUDE_FROM_ALL)
target_link_libraries(Il2CppModFramework INTERFACE StackTracer)
set_property(TARGET StackTracer PROPERTY FOLDER "Il2CppModFramework/debuggers")

add_subdirectory("${ICMF_SOURCE_DIR}/libs/static_lambda" "libs/static_lambda" EXCLUDE_FROM_ALL)
set_common_flags(static_lambda)
target_link_libraries(Il2CppModFramework INTERFACE static_lambda)
set_property(TARGET static_lambda PROPERTY FOLDER "Il2CppModFramework/libs")

set(SIMDUTF_TESTS OFF CACHE BOOL "" FORCE)
set(SIMDUTF_TOOLS OFF CACHE BOOL "" FORCE)
set(SIMDUTF_ICONV OFF CACHE BOOL "" FORCE)
add_subdirectory("${ICMF_SOURCE_DIR}/libs/simdutf" "libs/simdutf" EXCLUDE_FROM_ALL)
set_common_flags(simdutf)
target_link_libraries(Il2CppModFramework INTERFACE simdutf)
set_property(TARGET simdutf PROPERTY FOLDER "Il2CppModFramework/libs")

# no sources
add_subdirectory("${ICMF_SOURCE_DIR}/libs/json" "libs/json" EXCLUDE_FROM_ALL)
#set_common_flags(nlohmann_json)
#target_link_libraries(Il2CppModFramework INTERFACE nlohmann_json)
#set_property(TARGET json PROPERTY FOLDER "Il2CppModFramework/libs")

add_subdirectory("${ICMF_SOURCE_DIR}/GameAssembly" "GameAssembly" EXCLUDE_FROM_ALL)
target_link_libraries(Il2CppModFramework INTERFACE GameAssembly)
set_property(TARGET GameAssembly PROPERTY FOLDER "Il2CppModFramework")
set_property(TARGET GameAssembly_optimized PROPERTY FOLDER "Il2CppModFramework")
set_property(TARGET GameAssembly_autogen PROPERTY FOLDER "Il2CppModFramework")

if(ICMF_ENABLE_IMGUI)
	add_subdirectory("${ICMF_SOURCE_DIR}/libs/imgui_wrapper" "imgui" EXCLUDE_FROM_ALL)
	target_link_libraries(Il2CppModFramework INTERFACE imgui)
	set_property(TARGET imgui PROPERTY FOLDER "Il2CppModFramework/libs")
endif()
