cmake_minimum_required(VERSION 3.13)
project("GameAssembly")

include("${ICMF_SOURCE_DIR}/cmake/config_common.cmake")
include("${ICMF_SOURCE_DIR}/cmake/add_optimized.cmake")
include("${ICMF_SOURCE_DIR}/cmake/add_autogen.cmake")

config_common(GameAssembly STATIC)
target_precompile_headers(GameAssembly PRIVATE src/pch.hpp)
target_include_directories(GameAssembly PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

target_sources(GameAssembly PRIVATE "GameAssembly.natvis")

add_autogen(GameAssembly)

add_optimized(GameAssembly_optimized STATIC "${CMAKE_CURRENT_LIST_DIR}/optimized/update_patch.cpp")
target_link_libraries(GameAssembly GameAssembly_optimized)

target_compile_definitions(
	GameAssembly
	PRIVATE ICMF_UNITY_VERSION=${ICMF_UNITY_VERSION}
	PRIVATE ICMF_UNITY_VERSION_NUM=${ICMF_UNITY_VERSION_NUM}
)

target_compile_definitions(
	GameAssembly_optimized
	PRIVATE ICMF_UNITY_VERSION=${ICMF_UNITY_VERSION}
	PRIVATE ICMF_UNITY_VERSION_NUM=${ICMF_UNITY_VERSION_NUM}
)

target_compile_definitions(
	GameAssembly_autogen
	PRIVATE ICMF_UNITY_VERSION=${ICMF_UNITY_VERSION}
	PRIVATE ICMF_UNITY_VERSION_NUM=${ICMF_UNITY_VERSION_NUM}
)
