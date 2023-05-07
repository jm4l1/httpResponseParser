cmake_minimum_required(VERSION 3.25)

set(project httpResponseParser)
project(httpResponseParser)

add_definitions(-std=c++20)

set(CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS,"-${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(tests)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(${project} main.cpp ${SOURCES})

install(TARGETS ${project})