cmake_minimum_required(VERSION 3.20)

project(melty_web CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)

if (EMSCRIPTEN)
    # Web target will be configured here
else()
    add_executable(melty_test src/platform/native/main.cpp)
endif()
