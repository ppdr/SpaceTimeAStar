cmake_minimum_required(VERSION 3.30)

project(SpaceTimeAStar)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/SpaceTimeAStar)

file(GLOB SOURCES "src/*.cpp")
add_executable(stastar ${SOURCES})
