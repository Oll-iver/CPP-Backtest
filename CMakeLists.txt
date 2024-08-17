cmake_minimum_required(VERSION 3.10)
project(BacktestingFramework)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Gather all source files
file(GLOB SOURCES "src/*.cpp")

# Create the core library
add_library(BacktestingCore ${SOURCES})

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Create test executable and link with the core library and Google Test
add_executable(BacktestingTests tests/AllTests.cpp)
target_link_libraries(BacktestingTests BacktestingCore gtest gtest_main)

add_test(NAME BacktestingTests COMMAND BacktestingTests)
