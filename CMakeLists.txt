cmake_minimum_required(VERSION 3.10)
project(BacktestingFramework)

set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(include)

# Gather all source files from src directory
file(GLOB SOURCES "src/*.cpp")

# Create the core library from the source files
add_library(BacktestingCore ${SOURCES})

# Google Test setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Specify output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Specify the test file explicitly
add_executable(BacktestingTests tests/AllTests.cpp)
target_link_libraries(BacktestingTests BacktestingCore gtest gtest_main)

# Add a test to the CMake test suite
add_test(NAME BacktestingTests COMMAND BacktestingTests)

# Create the main executable and link with the core library
add_executable(BacktestingApp src/main.cpp)
target_link_libraries(BacktestingApp BacktestingCore)
