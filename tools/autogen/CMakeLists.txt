cmake_minimum_required(VERSION 3.13)
project("autogen")

include("${ICMF_SOURCE_DIR}/cmake/config_mini.cmake")
include("${ICMF_SOURCE_DIR}/cmake/create_source_filters.cmake")

set(AUTOGEN_SOURCES
	main.cpp
	SimpleParser.hpp
	SimpleParser.cpp
	SimpleGenerator.hpp
	SimpleGenerator.cpp
)

config_mini(autogen EXECUTABLE "${AUTOGEN_SOURCES}")
create_source_filters(autogen ${CMAKE_CURRENT_SOURCE_DIR})
