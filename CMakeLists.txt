cmake_minimum_required(VERSION 3.10)

project(margv)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_library(margv INTERFACE)
target_include_directories(margv INTERFACE include)

add_subdirectory(apps)
