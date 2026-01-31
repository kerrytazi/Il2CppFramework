find_path(DiaSDK_INCLUDE_DIR
	NAMES dia2.h
	PATHS
		"$ENV{ProgramFiles}/Microsoft Visual Studio/*/DIA SDK/include"
		"$ENV{VSINSTALLDIR}/DIA SDK/include"
		"C:/Program Files/Microsoft Visual Studio/DIA SDK/include"
	DOC "DIA SDK Include Directory"
)

find_library(DiaSDK_LIBRARY
	NAMES diaguids.lib
	PATHS
		"$ENV{ProgramFiles}/Microsoft Visual Studio/*/DIA SDK/lib/amd64"
		"$ENV{VSINSTALLDIR}/DIA SDK/lib/amd64"
		"C:/Program Files/Microsoft Visual Studio/DIA SDK/lib/amd64"
	DOC "DIA SDK Library"
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DiaSDK
	DEFAULT_MSG
	DiaSDK_INCLUDE_DIR
	DiaSDK_LIBRARY
)

if(DiaSDK_FOUND)
	set(DiaSDK_INCLUDE_DIRS ${DiaSDK_INCLUDE_DIR})
	set(DiaSDK_LIBRARIES ${DiaSDK_LIBRARY})
	mark_as_advanced(DiaSDK_INCLUDE_DIR DiaSDK_LIBRARY)
endif()
