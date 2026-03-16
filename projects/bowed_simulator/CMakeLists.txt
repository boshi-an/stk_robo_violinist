cmake_minimum_required(VERSION 3.15)
project(bowed_simulator LANGUAGES CXX)

# Layout: include/ for headers, src/ for sources
include_directories(${CMAKE_SOURCE_DIR}/projects/bowed_simulator/include)

# Library target for reuse
add_library(mybowed_lib src/MyBowed.cpp)
target_include_directories(mybowed_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/projects/bowed_simulator/include
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(mybowed_lib PUBLIC stk)

# Minimal quick start example target
add_executable(example_usage src/example_usage.cpp)
target_link_libraries(example_usage PRIVATE mybowed_lib)
set_target_properties(example_usage PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/projects/bowed_simulator/bin"
)

# Python / pybind11
set(PYBIND11_FINDPYTHON ON)
find_package(Python3 3.10 REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(mybowed_py pybind/MyBowedBindings.cpp)
target_link_libraries(mybowed_py PRIVATE mybowed_lib)
target_include_directories(mybowed_py PRIVATE
    ${CMAKE_SOURCE_DIR}/projects/bowed_simulator/include
    ${CMAKE_SOURCE_DIR}/include
)
set_target_properties(mybowed_py PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/projects/bowed_simulator/lib"
)