cmake_minimum_required(VERSION 3.20)
project(blackwell_runtime LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# CUDA architecture targets: Blackwell (sm_100), Ada (sm_89), Hopper (sm_90)
set(CMAKE_CUDA_ARCHITECTURES "89;90;100" CACHE STRING "CUDA architectures")

find_package(CUDA REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)

include_directories(include)

# Core runtime library
file(GLOB_RECURSE RUNTIME_SRC
    "src/*.cpp"
    "csrc/cuda/*.cu"
)

add_library(blackwell_runtime SHARED ${RUNTIME_SRC})
target_include_directories(blackwell_runtime PUBLIC include)
target_compile_options(blackwell_runtime PRIVATE
    $<$<COMPILE_LANGUAGE:CUDA>:
        -O3
        --use_fast_math
        -lineinfo
        --ptxas-options=-v
    >
)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
