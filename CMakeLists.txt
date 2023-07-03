cmake_minimum_required(VERSION 3.18)

project(Torsen)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(Torsen ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
