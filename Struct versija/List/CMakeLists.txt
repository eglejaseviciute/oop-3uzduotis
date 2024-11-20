cmake_minimum_required(VERSION 3.10)
project(List VERSION 1.0)

include_directories(Include)
file(GLOB SOURCES "src/*.cpp")

add_executable(List ${SOURCES})


set_property(TARGET List PROPERTY CXX_STANDARD 17)
