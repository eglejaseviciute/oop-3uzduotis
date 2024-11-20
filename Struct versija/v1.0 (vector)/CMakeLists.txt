cmake_minimum_required(VERSION 3.10)
project(v1.0_vector VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Include)
file(GLOB SOURCES "src/*.cpp")

add_executable(v1.0_vector_O1 ${SOURCES})
add_executable(v1.0_vector_O2 ${SOURCES})
add_executable(v1.0_vector_O3 ${SOURCES})

target_compile_options(v1.0_vector_O1 PRIVATE -O1)
target_compile_options(v1.0_vector_O2 PRIVATE -O2)
target_compile_options(v1.0_vector_O3 PRIVATE -O3)
