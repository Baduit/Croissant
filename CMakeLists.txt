cmake_minimum_required(VERSION 3.12)

project(CroissantProject VERSION 1.2.0 DESCRIPTION "Make comparisons great againg !")

option(EXAMPLE "EXAMPLE" ON)
option(TESTS "TESTS" ON)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(lib)

if (EXAMPLE)
	add_subdirectory(bin)                    
endif()

if (TESTS)
	include(CTest)
	include(addTest)
	enable_testing(MAKE_DIRECTORY test)
	add_subdirectory(test)
endif()