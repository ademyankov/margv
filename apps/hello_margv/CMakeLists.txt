cmake_minimum_required(VERSION 3.10)

project(hello_margv)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    src/hello_margv.cpp
)

target_link_libraries(${PROJECT_NAME} margv)
