cmake_minimum_required(VERSION 3.10)
project(v1.0_vector VERSION 1.0)

include_directories(Include)
file(GLOB SOURCES "src/*.cpp")

add_executable(v1.0_vector ${SOURCES})


set_property(TARGET v1.0_vector PROPERTY CXX_STANDARD 17)