cmake_minimum_required(VERSION 2.8.9)
project (Engine)
SET(CMAKE_CXX_FLAGS "-std=c++14 -O3 -Wall" )

include_directories(tinyxml2/*.h)
include_directories(*.h)


file(GLOB SOURCES "tinyxml2/*.cpp")
add_executable(Engine ${SOURCES})
