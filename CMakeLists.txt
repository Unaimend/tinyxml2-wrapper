cmake_minimum_required(VERSION 2.8.7)
project (test_tinyxml2_wrapper)
SET(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall" )

include_directories(tinyxml2/*.h)
include_directories(*.h)



add_executable(test_tinyxml2_wrapper  tinyxml2/tinyxml2.cpp test.cpp catch.h)
