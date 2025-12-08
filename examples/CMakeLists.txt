cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(example_one main.c)
target_link_libraries(example_one Bird)
