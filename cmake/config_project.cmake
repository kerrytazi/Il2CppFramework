function(config_project target_name)
	target_compile_features(${target_name} PRIVATE cxx_std_23)
	set_target_properties(${target_name} PROPERTIES CXX_SCAN_FOR_MODULES OFF)

	if(MSVC)
		target_compile_options(${target_name}
			PRIVATE
				/W4 /WX /permissive- /utf-8
				/Zc:__cplusplus /Zc:preprocessor /Zc:lambda /Zc:templateScope
				/Zc:rvalueCast /Zc:ternary /Zc:referenceBinding
		)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
		target_compile_options(${target_name}
			PRIVATE
				-Wall -Wextra -Wpedantic
		)
	endif()

	get_target_property(target_SOURCE_DIR ${target_name} SOURCE_DIR)
	get_target_property(target_SOURCES ${target_name} SOURCES)
	get_target_property(target_HEADERS ${target_name} HEADER_SET)

	source_group(TREE ${target_SOURCE_DIR}
		FILES
			${target_SOURCES}
			${target_HEADERS}
	)
endfunction()
