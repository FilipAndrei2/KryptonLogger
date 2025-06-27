cmake_minimum_required(VERSION 3.31)
project(krypton)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(krypton STATIC ${SOURCES})

target_include_directories(krypton PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_precompile_headers(krypton PRIVATE include/kr/internal/pch.hpp)