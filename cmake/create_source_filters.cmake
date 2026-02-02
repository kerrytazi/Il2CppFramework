# source_dir is usually CMAKE_CURRENT_SOURCE_DIR
function(create_source_filters target_name source_dir)
	get_target_property(source_files ${target_name} SOURCES)

	foreach(source_file ${source_files})
		get_filename_component(abs_path ${source_file} ABSOLUTE)
		file(RELATIVE_PATH rel_path ${source_dir} ${abs_path})

		get_filename_component(dir_path ${rel_path} DIRECTORY)

		if(dir_path)
			string(REPLACE "/" "\\" filter_name "${dir_path}")
			source_group("${filter_name}" FILES ${source_file})
		endif()
	endforeach()
endfunction()
