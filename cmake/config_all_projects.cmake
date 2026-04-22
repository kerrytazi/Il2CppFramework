function(config_all_projects)
	set(INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

	# NOTE: avx2 might not work on older hardware
	if(MSVC)
		set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /MP /fp:fast /arch:AVX2")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /fp:fast /arch:AVX2 /GR-")
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
		set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -mavx2")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -mavx2 -fno-rtti")
	endif()
endfunction()
