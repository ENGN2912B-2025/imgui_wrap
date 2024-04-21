cmake_minimum_required(VERSION 3.22.1)

project(imgui_wrap)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(build_config)

add_subdirectory(3rd-party)
add_subdirectory(src)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
  message(STATUS "Stand-alone build: enable examples")
  add_subdirectory(examples)
endif()