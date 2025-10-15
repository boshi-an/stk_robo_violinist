project(bowed_simulator)

# Layout: include/ for headers, src/ for sources
include_directories(${CMAKE_SOURCE_DIR}/projects/bowed_simulator/include)

# Library target for reuse
add_library(mybowed_lib src/MyBowed.cpp)
target_include_directories(mybowed_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/projects/bowed_simulator/include
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(mybowed_lib PUBLIC stk)

# Executables
add_executable(mybowed src/mybowed.cpp)
target_link_libraries(mybowed PRIVATE mybowed_lib)

# Set output directory
set_target_properties(mybowed PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/projects/bowed_simulator/bin"
)

# Minimal quick start example target
add_executable(example_usage src/example_usage.cpp)
target_link_libraries(example_usage PRIVATE mybowed_lib)
set_target_properties(example_usage PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/projects/bowed_simulator/bin"
)

# Pick one exact version you want
set(PYBIND11_FINDPYTHON ON)
find_package(Python3 3.10 EXACT COMPONENTS Interpreter Development.Module REQUIRED)

# (optional, helps older pybind11)
set(Python_EXECUTABLE ${Python3_EXECUTABLE})

find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(mybowed_py src/MyBowed.cpp pybind/MyBowedBindings.cpp)
target_link_libraries(mybowed_py PRIVATE mybowed_lib)
target_include_directories(mybowed_py PRIVATE
    ${CMAKE_SOURCE_DIR}/projects/bowed_simulator/include
    ${CMAKE_SOURCE_DIR}/include
)
# Write the module next to quick_start.py for import
set_target_properties(mybowed_py PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/projects/bowed_simulator/lib"
)
