include("${ICMF_SOURCE_DIR}/cmake/config_mini.cmake")
include("${ICMF_SOURCE_DIR}/cmake/create_source_filters.cmake")

function(config_common target_name library_type)
	file(GLOB_RECURSE target_sources
		"${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	)

	config_mini(${target_name} ${library_type} "${target_sources}")
	create_source_filters(${target_name} ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()
