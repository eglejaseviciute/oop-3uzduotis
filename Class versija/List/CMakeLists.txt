cmake_minimum_required(VERSION 3.10)
project(List VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Include)
file(GLOB SOURCES "src/*.cpp")

add_executable(List_O1 ${SOURCES})
add_executable(List_O2 ${SOURCES})
add_executable(List_O3 ${SOURCES})

target_compile_options(List_O1 PRIVATE -O1)
target_compile_options(List_O2 PRIVATE -O2)
target_compile_options(List_O3 PRIVATE -O3)