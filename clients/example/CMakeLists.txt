cmake_minimum_required(VERSION 3.13)
project("example_client")

include("${CMAKE_CURRENT_LIST_DIR}/../../cmake/config_client.cmake")

config_client(
	example_client
	"${CMAKE_CURRENT_LIST_DIR}"
	"${CMAKE_CURRENT_LIST_DIR}/../.."
)
