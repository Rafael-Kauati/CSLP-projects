# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6

# Include any dependencies generated for this target.
include CMakeFiles/GolombCodingTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GolombCodingTests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GolombCodingTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GolombCodingTests.dir/flags.make

CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o: CMakeFiles/GolombCodingTests.dir/flags.make
CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o: Golomb_Decoder.cpp
CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o: CMakeFiles/GolombCodingTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o -MF CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o.d -o CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/Golomb_Decoder.cpp

CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/Golomb_Decoder.cpp > CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.i

CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/Golomb_Decoder.cpp -o CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.s

CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o: CMakeFiles/GolombCodingTests.dir/flags.make
CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o: Golomb_Enconder.cpp
CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o: CMakeFiles/GolombCodingTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o -MF CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o.d -o CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/Golomb_Enconder.cpp

CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/Golomb_Enconder.cpp > CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.i

CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/Golomb_Enconder.cpp -o CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.s

# Object files for target GolombCodingTests
GolombCodingTests_OBJECTS = \
"CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o" \
"CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o"

# External object files for target GolombCodingTests
GolombCodingTests_EXTERNAL_OBJECTS =

GolombCodingTests: CMakeFiles/GolombCodingTests.dir/Golomb_Decoder.cpp.o
GolombCodingTests: CMakeFiles/GolombCodingTests.dir/Golomb_Enconder.cpp.o
GolombCodingTests: CMakeFiles/GolombCodingTests.dir/build.make
GolombCodingTests: CMakeFiles/GolombCodingTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable GolombCodingTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GolombCodingTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GolombCodingTests.dir/build: GolombCodingTests
.PHONY : CMakeFiles/GolombCodingTests.dir/build

CMakeFiles/GolombCodingTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GolombCodingTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GolombCodingTests.dir/clean

CMakeFiles/GolombCodingTests.dir/depend:
	cd /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_3/Program_6/CMakeFiles/GolombCodingTests.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/GolombCodingTests.dir/depend

