cmake_minimum_required(VERSION 3.25)

add_definitions(-std=c++20)

set(this tests)

project(${this} C CXX)

file(GLOB SOURCES "src/*.cpp" "../src/*.cpp")

add_executable(${this} ${SOURCES})

include_directories(include "../include")

set_target_properties(${this} PROPERTIES FOLDER tests)

target_include_directories(${this} PRIVATE)

install(TARGETS ${this})