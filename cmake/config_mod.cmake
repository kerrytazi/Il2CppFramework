include("${ICMF_SOURCE_DIR}/cmake/config_common.cmake")

function(config_mod target_name)
	message(STATUS "config_client: ${target_name}")

	config_common(${target_name} SHARED)

	target_sources(${target_name} PRIVATE "${ICMF_SOURCE_DIR}/bootstrap/bootstrap_win32.cpp")

	target_link_libraries(${target_name} Il2CppModFramework)

	target_compile_definitions(
		${target_name} PRIVATE
		ICMF_UNITY_VERSION=${ICMF_UNITY_VERSION}
		ICMF_UNITY_VERSION_NUM=${ICMF_UNITY_VERSION_NUM}
	)
endfunction()
