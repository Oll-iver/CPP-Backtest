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
include CMakeFiles/BacktestingFramework.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BacktestingFramework.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BacktestingFramework.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BacktestingFramework.dir/flags.make

CMakeFiles/BacktestingFramework.dir/src/main.cpp.o: CMakeFiles/BacktestingFramework.dir/flags.make
CMakeFiles/BacktestingFramework.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/BacktestingFramework.dir/src/main.cpp.o: CMakeFiles/BacktestingFramework.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BacktestingFramework.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BacktestingFramework.dir/src/main.cpp.o -MF CMakeFiles/BacktestingFramework.dir/src/main.cpp.o.d -o CMakeFiles/BacktestingFramework.dir/src/main.cpp.o -c "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/src/main.cpp"

CMakeFiles/BacktestingFramework.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BacktestingFramework.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/src/main.cpp" > CMakeFiles/BacktestingFramework.dir/src/main.cpp.i

CMakeFiles/BacktestingFramework.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BacktestingFramework.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/src/main.cpp" -o CMakeFiles/BacktestingFramework.dir/src/main.cpp.s

# Object files for target BacktestingFramework
BacktestingFramework_OBJECTS = \
"CMakeFiles/BacktestingFramework.dir/src/main.cpp.o"

# External object files for target BacktestingFramework
BacktestingFramework_EXTERNAL_OBJECTS =

BacktestingFramework: CMakeFiles/BacktestingFramework.dir/src/main.cpp.o
BacktestingFramework: CMakeFiles/BacktestingFramework.dir/build.make
BacktestingFramework: libBacktestingCore.a
BacktestingFramework: CMakeFiles/BacktestingFramework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable BacktestingFramework"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BacktestingFramework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BacktestingFramework.dir/build: BacktestingFramework
.PHONY : CMakeFiles/BacktestingFramework.dir/build

CMakeFiles/BacktestingFramework.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BacktestingFramework.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BacktestingFramework.dir/clean

CMakeFiles/BacktestingFramework.dir/depend:
	cd "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build" "/home/oli/Documents/Portfolio/CPP/Backtesting Framework/build/CMakeFiles/BacktestingFramework.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/BacktestingFramework.dir/depend

