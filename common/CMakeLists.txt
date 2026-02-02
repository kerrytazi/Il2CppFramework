cmake_minimum_required(VERSION 3.13)
project("common")

include("${ICMF_SOURCE_DIR}/cmake/config_common.cmake")
include("${ICMF_SOURCE_DIR}/cmake/add_optimized.cmake")

config_common(common STATIC)
target_precompile_headers(common PRIVATE src/pch.hpp)

if(ICMF_ENABLE_IMGUI)
	add_optimized(common_optimized STATIC "${CMAKE_CURRENT_LIST_DIR}/optimized/ImGuiHook.cpp")
	target_link_libraries(common common_optimized)
endif()

if(ICMF_LOADER STREQUAL "DLL_INJECTOR")
	target_compile_definitions(common PRIVATE ICMF_LOADER_DLL_INJECTOR=1)
elseif(ICMF_LOADER STREQUAL "MANUAL_MAPPER")
	target_compile_definitions(common PRIVATE ICMF_LOADER_MANUAL_MAPPER=1)
else()
	message(FATAL_ERROR "No loader selected.\nUse on of:\n\tcmake -D ICMF_LOADER=DLL_INJECTOR\n\tcmake -D ICMF_LOADER=MANUAL_MAPPER")
endif()
