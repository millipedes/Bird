cmake_minimum_required(VERSION 3.25)
project(Bird)

set(CMAKE_C_EXTENSIONS OFF)

################
# Core Library #
################
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(SRC_FILES
  ${SRC_DIR}/core/bezier.c
  ${SRC_DIR}/core/canvas.c
  ${SRC_DIR}/core/ellipse.c
  ${SRC_DIR}/core/matrix3d.c
  ${SRC_DIR}/impl/png_translation.c
)

include_directories(
  ${SRC_DIR}
)

find_package(PNG REQUIRED)

add_library(Bird ${SRC_FILES})

target_link_libraries(Bird
  PNG::PNG
  m
)

option(BUILD_TESTS "Build Test Suite" OFF)

if(BUILD_TESTS)
  add_subdirectory(./test)
endif()

option(BUILD_EXAMPLES "Build Examples" ON)

if(BUILD_EXAMPLES)
  add_subdirectory(./examples)
endif()
