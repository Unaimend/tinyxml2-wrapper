cmake_minimum_required(VERSION 2.8.7)
project(test_tinyxml2_wrapper)
SET(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall" )

include_directories(tinyxml2/*.h)
include_directories(*.h)

add_executable(test_tinyxml2_wrapper  tinyxml2/tinyxml2.cpp test.cpp catch.h)
add_custom_target(unit
COMMENT "Running unittests"
COMMAND ./test_tinyxml2_wrapper
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(doc
COMMAND sh run_doxy
)
endif(DOXYGEN_FOUND)

