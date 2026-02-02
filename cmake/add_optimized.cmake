include("${CMAKE_CURRENT_LIST_DIR}/config_mini.cmake")
include("${ICMF_SOURCE_DIR}/cmake/create_source_filters.cmake")

function(add_optimized target_name library_type target_sources)
	config_mini(${target_name} ${library_type} "${target_sources}")
	create_source_filters(${target_name} ${CMAKE_CURRENT_SOURCE_DIR})

	get_target_property(${target_name}_options ${target_name} COMPILE_OPTIONS)
	string(REPLACE "/Ob0;/Od;/RTC1" "/O2;/Ob1" ${target_name}_options_new "${${target_name}_options}")
	set_target_properties(${target_name} PROPERTIES COMPILE_OPTIONS "${${target_name}_options_new}")
endfunction()
