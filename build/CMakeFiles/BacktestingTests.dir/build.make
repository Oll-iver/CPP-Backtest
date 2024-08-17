# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/oli/Documents/Portfolio/CPP/Backtesting Framework"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build"

# Include any dependencies generated for this target.
include CMakeFiles/BacktestingTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BacktestingTests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BacktestingTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BacktestingTests.dir/flags.make

CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o: CMakeFiles/BacktestingTests.dir/flags.make
CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o: ../tests/AllTests.cpp
CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o: CMakeFiles/BacktestingTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o -MF CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o.d -o CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o -c "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/tests/AllTests.cpp"

CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/tests/AllTests.cpp" > CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.i

CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/tests/AllTests.cpp" -o CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.s

# Object files for target BacktestingTests
BacktestingTests_OBJECTS = \
"CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o"

# External object files for target BacktestingTests
BacktestingTests_EXTERNAL_OBJECTS =

BacktestingTests: CMakeFiles/BacktestingTests.dir/tests/AllTests.cpp.o
BacktestingTests: CMakeFiles/BacktestingTests.dir/build.make
BacktestingTests: libBacktestingCore.a
BacktestingTests: lib/libgtest.a
BacktestingTests: lib/libgtest_main.a
BacktestingTests: lib/libgtest.a
BacktestingTests: CMakeFiles/BacktestingTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BacktestingTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BacktestingTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BacktestingTests.dir/build: BacktestingTests
.PHONY : CMakeFiles/BacktestingTests.dir/build

CMakeFiles/BacktestingTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BacktestingTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BacktestingTests.dir/clean

CMakeFiles/BacktestingTests.dir/depend:
	cd "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build/CMakeFiles/BacktestingTests.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/BacktestingTests.dir/depend
