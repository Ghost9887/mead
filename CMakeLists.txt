cmake_minimum_required(VERSION 3.10)
project(mead)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

file(GLOB_RECURSE APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
)

add_library(mead STATIC ${APP_SOURCES})

target_include_directories(mead
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
