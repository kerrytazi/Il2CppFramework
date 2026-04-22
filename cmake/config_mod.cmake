include(${CMAKE_CURRENT_LIST_DIR}/config_project.cmake)

function(config_mod target_name)
	config_project(${target_name})
	target_link_libraries(${target_name} PRIVATE Il2CppModFramework)

	if(WIN32)
		get_target_property(Il2CppModFramework_SOURCE_DIR Il2CppModFramework SOURCE_DIR)
		target_sources(${target_name}
			PRIVATE
				"${Il2CppModFramework_SOURCE_DIR}/src/bootstrap/bootstrap_win32.cpp"
		)
	endif()
endfunction()
