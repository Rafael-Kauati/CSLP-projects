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
CMAKE_SOURCE_DIR = /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5

# Include any dependencies generated for this target.
include CMakeFiles/unit_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/unit_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/unit_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/unit_tests.dir/flags.make

CMakeFiles/unit_tests.dir/unit_tests.cpp.o: CMakeFiles/unit_tests.dir/flags.make
CMakeFiles/unit_tests.dir/unit_tests.cpp.o: unit_tests.cpp
CMakeFiles/unit_tests.dir/unit_tests.cpp.o: CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/unit_tests.dir/unit_tests.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/unit_tests.dir/unit_tests.cpp.o -MF CMakeFiles/unit_tests.dir/unit_tests.cpp.o.d -o CMakeFiles/unit_tests.dir/unit_tests.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/unit_tests.cpp

CMakeFiles/unit_tests.dir/unit_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/unit_tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/unit_tests.cpp > CMakeFiles/unit_tests.dir/unit_tests.cpp.i

CMakeFiles/unit_tests.dir/unit_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/unit_tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/unit_tests.cpp -o CMakeFiles/unit_tests.dir/unit_tests.cpp.s

CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o: CMakeFiles/unit_tests.dir/flags.make
CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o: Golomb/Golomb.cpp
CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o: CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o -MF CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o.d -o CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb.cpp

CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb.cpp > CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.i

CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb.cpp -o CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.s

CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o: CMakeFiles/unit_tests.dir/flags.make
CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o: Golomb/Golomb_Encoder.cpp
CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o: CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o -MF CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o.d -o CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb_Encoder.cpp

CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb_Encoder.cpp > CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.i

CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb_Encoder.cpp -o CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.s

CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o: CMakeFiles/unit_tests.dir/flags.make
CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o: Golomb/Golomb_Decoder.cpp
CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o: CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o -MF CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o.d -o CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb_Decoder.cpp

CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb_Decoder.cpp > CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.i

CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/Golomb/Golomb_Decoder.cpp -o CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.s

CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o: CMakeFiles/unit_tests.dir/flags.make
CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o: HybridCodec/BlockSearch.cpp
CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o: CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o -MF CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o.d -o CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/HybridCodec/BlockSearch.cpp

CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/HybridCodec/BlockSearch.cpp > CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.i

CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/HybridCodec/BlockSearch.cpp -o CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.s

CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o: CMakeFiles/unit_tests.dir/flags.make
CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o: HybridCodec/HybridCodec.cpp
CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o: CMakeFiles/unit_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o -MF CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o.d -o CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o -c /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/HybridCodec/HybridCodec.cpp

CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/HybridCodec/HybridCodec.cpp > CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.i

CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/HybridCodec/HybridCodec.cpp -o CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.s

# Object files for target unit_tests
unit_tests_OBJECTS = \
"CMakeFiles/unit_tests.dir/unit_tests.cpp.o" \
"CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o" \
"CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o" \
"CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o" \
"CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o" \
"CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o"

# External object files for target unit_tests
unit_tests_EXTERNAL_OBJECTS =

unit_tests: CMakeFiles/unit_tests.dir/unit_tests.cpp.o
unit_tests: CMakeFiles/unit_tests.dir/Golomb/Golomb.cpp.o
unit_tests: CMakeFiles/unit_tests.dir/Golomb/Golomb_Encoder.cpp.o
unit_tests: CMakeFiles/unit_tests.dir/Golomb/Golomb_Decoder.cpp.o
unit_tests: CMakeFiles/unit_tests.dir/HybridCodec/BlockSearch.cpp.o
unit_tests: CMakeFiles/unit_tests.dir/HybridCodec/HybridCodec.cpp.o
unit_tests: CMakeFiles/unit_tests.dir/build.make
unit_tests: /usr/local/lib/libopencv_gapi.so.4.8.0
unit_tests: /usr/local/lib/libopencv_stitching.so.4.8.0
unit_tests: /usr/local/lib/libopencv_aruco.so.4.8.0
unit_tests: /usr/local/lib/libopencv_bgsegm.so.4.8.0
unit_tests: /usr/local/lib/libopencv_bioinspired.so.4.8.0
unit_tests: /usr/local/lib/libopencv_ccalib.so.4.8.0
unit_tests: /usr/local/lib/libopencv_dnn_objdetect.so.4.8.0
unit_tests: /usr/local/lib/libopencv_dnn_superres.so.4.8.0
unit_tests: /usr/local/lib/libopencv_dpm.so.4.8.0
unit_tests: /usr/local/lib/libopencv_face.so.4.8.0
unit_tests: /usr/local/lib/libopencv_freetype.so.4.8.0
unit_tests: /usr/local/lib/libopencv_fuzzy.so.4.8.0
unit_tests: /usr/local/lib/libopencv_hdf.so.4.8.0
unit_tests: /usr/local/lib/libopencv_hfs.so.4.8.0
unit_tests: /usr/local/lib/libopencv_img_hash.so.4.8.0
unit_tests: /usr/local/lib/libopencv_intensity_transform.so.4.8.0
unit_tests: /usr/local/lib/libopencv_line_descriptor.so.4.8.0
unit_tests: /usr/local/lib/libopencv_mcc.so.4.8.0
unit_tests: /usr/local/lib/libopencv_quality.so.4.8.0
unit_tests: /usr/local/lib/libopencv_rapid.so.4.8.0
unit_tests: /usr/local/lib/libopencv_reg.so.4.8.0
unit_tests: /usr/local/lib/libopencv_rgbd.so.4.8.0
unit_tests: /usr/local/lib/libopencv_saliency.so.4.8.0
unit_tests: /usr/local/lib/libopencv_stereo.so.4.8.0
unit_tests: /usr/local/lib/libopencv_structured_light.so.4.8.0
unit_tests: /usr/local/lib/libopencv_superres.so.4.8.0
unit_tests: /usr/local/lib/libopencv_surface_matching.so.4.8.0
unit_tests: /usr/local/lib/libopencv_tracking.so.4.8.0
unit_tests: /usr/local/lib/libopencv_videostab.so.4.8.0
unit_tests: /usr/local/lib/libopencv_wechat_qrcode.so.4.8.0
unit_tests: /usr/local/lib/libopencv_xfeatures2d.so.4.8.0
unit_tests: /usr/local/lib/libopencv_xobjdetect.so.4.8.0
unit_tests: /usr/local/lib/libopencv_xphoto.so.4.8.0
unit_tests: /usr/local/lib/libopencv_shape.so.4.8.0
unit_tests: /usr/local/lib/libopencv_highgui.so.4.8.0
unit_tests: /usr/local/lib/libopencv_datasets.so.4.8.0
unit_tests: /usr/local/lib/libopencv_plot.so.4.8.0
unit_tests: /usr/local/lib/libopencv_text.so.4.8.0
unit_tests: /usr/local/lib/libopencv_ml.so.4.8.0
unit_tests: /usr/local/lib/libopencv_phase_unwrapping.so.4.8.0
unit_tests: /usr/local/lib/libopencv_optflow.so.4.8.0
unit_tests: /usr/local/lib/libopencv_ximgproc.so.4.8.0
unit_tests: /usr/local/lib/libopencv_video.so.4.8.0
unit_tests: /usr/local/lib/libopencv_videoio.so.4.8.0
unit_tests: /usr/local/lib/libopencv_imgcodecs.so.4.8.0
unit_tests: /usr/local/lib/libopencv_objdetect.so.4.8.0
unit_tests: /usr/local/lib/libopencv_calib3d.so.4.8.0
unit_tests: /usr/local/lib/libopencv_dnn.so.4.8.0
unit_tests: /usr/local/lib/libopencv_features2d.so.4.8.0
unit_tests: /usr/local/lib/libopencv_flann.so.4.8.0
unit_tests: /usr/local/lib/libopencv_photo.so.4.8.0
unit_tests: /usr/local/lib/libopencv_imgproc.so.4.8.0
unit_tests: /usr/local/lib/libopencv_core.so.4.8.0
unit_tests: CMakeFiles/unit_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable unit_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unit_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/unit_tests.dir/build: unit_tests
.PHONY : CMakeFiles/unit_tests.dir/build

CMakeFiles/unit_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unit_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unit_tests.dir/clean

CMakeFiles/unit_tests.dir/depend:
	cd /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5 /home/frostywolf/Documents/GitReps/CSLP-projects/Projeto/Deliverable_5/CMakeFiles/unit_tests.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/unit_tests.dir/depend

