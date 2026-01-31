cmake_minimum_required(VERSION 3.13)
project("StackTracer")

include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/config_common.cmake")

config_common(StackTracer STATIC)

if(UC_STACK_TRACER STREQUAL "DIA")
	include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/find_dia_sdk.cmake")
	message(STATUS ${DiaSDK_INCLUDE_DIRS})
	message(STATUS ${DiaSDK_LIBRARIES})
	target_include_directories(StackTracer PRIVATE ${DiaSDK_INCLUDE_DIRS})
	target_link_libraries(StackTracer ${DiaSDK_LIBRARIES})
	target_compile_definitions(StackTracer PRIVATE UC_STACK_TRACER_DIA=1)
elseif(UC_STACK_TRACER STREQUAL "DBGHELP")
	target_compile_definitions(StackTracer PRIVATE UC_STACK_TRACER_DBGHELP=1)
else()
	target_compile_definitions(StackTracer PRIVATE UC_STACK_TRACER_NONE=1)
endif()
