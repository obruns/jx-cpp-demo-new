cmake_minimum_required(VERSION 3.10)

project(demo
    VERSION 1.0.0
    DESCRIPTION "foobar todo"
    LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cxxDefaults INTERFACE)

target_compile_options(cxxDefaults INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Werror -Wno-error=unused-variable
)

enable_testing()

add_subdirectory(src/)
add_subdirectory(test/)
