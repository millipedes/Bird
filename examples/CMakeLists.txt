cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_EXTENSIONS OFF)

add_executable(example_one main.c)
target_link_libraries(example_one Bird)
