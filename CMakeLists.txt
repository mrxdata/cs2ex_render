cmake_minimum_required(VERSION 3.10)
project(cs2ex_render)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    src/main.cpp
)

add_executable(cs2ex_render ${SOURCES})

target_link_libraries(cs2ex_render d3d11 d3dcompiler)
