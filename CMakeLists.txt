cmake_minimum_required(VERSION 3.9)
project(jsonutil VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

# This project requires C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAPIDJSON_ROOT_DIR third_party/rapidjson)

include_directories(${RAPIDJSON_ROOT_DIR}/include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(jsonutil src/jsonutil.cpp include/jsonutil/jsonutil.hpp)

add_subdirectory(example)
