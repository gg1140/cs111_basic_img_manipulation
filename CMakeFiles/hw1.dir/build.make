# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gordonchan/codes/cs111_spring2019/hw1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gordonchan/codes/cs111_spring2019/hw1

# Include any dependencies generated for this target.
include CMakeFiles/hw1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw1.dir/flags.make

CMakeFiles/hw1.dir/hw1.cpp.o: CMakeFiles/hw1.dir/flags.make
CMakeFiles/hw1.dir/hw1.cpp.o: hw1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gordonchan/codes/cs111_spring2019/hw1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw1.dir/hw1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw1.dir/hw1.cpp.o -c /home/gordonchan/codes/cs111_spring2019/hw1/hw1.cpp

CMakeFiles/hw1.dir/hw1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1.dir/hw1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gordonchan/codes/cs111_spring2019/hw1/hw1.cpp > CMakeFiles/hw1.dir/hw1.cpp.i

CMakeFiles/hw1.dir/hw1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1.dir/hw1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gordonchan/codes/cs111_spring2019/hw1/hw1.cpp -o CMakeFiles/hw1.dir/hw1.cpp.s

# Object files for target hw1
hw1_OBJECTS = \
"CMakeFiles/hw1.dir/hw1.cpp.o"

# External object files for target hw1
hw1_EXTERNAL_OBJECTS =

hw1: CMakeFiles/hw1.dir/hw1.cpp.o
hw1: CMakeFiles/hw1.dir/build.make
hw1: /usr/local/lib/libopencv_dnn.so.4.1.0
hw1: /usr/local/lib/libopencv_gapi.so.4.1.0
hw1: /usr/local/lib/libopencv_ml.so.4.1.0
hw1: /usr/local/lib/libopencv_objdetect.so.4.1.0
hw1: /usr/local/lib/libopencv_photo.so.4.1.0
hw1: /usr/local/lib/libopencv_stitching.so.4.1.0
hw1: /usr/local/lib/libopencv_video.so.4.1.0
hw1: /usr/local/lib/libopencv_calib3d.so.4.1.0
hw1: /usr/local/lib/libopencv_features2d.so.4.1.0
hw1: /usr/local/lib/libopencv_flann.so.4.1.0
hw1: /usr/local/lib/libopencv_highgui.so.4.1.0
hw1: /usr/local/lib/libopencv_videoio.so.4.1.0
hw1: /usr/local/lib/libopencv_imgcodecs.so.4.1.0
hw1: /usr/local/lib/libopencv_imgproc.so.4.1.0
hw1: /usr/local/lib/libopencv_core.so.4.1.0
hw1: CMakeFiles/hw1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gordonchan/codes/cs111_spring2019/hw1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw1.dir/build: hw1

.PHONY : CMakeFiles/hw1.dir/build

CMakeFiles/hw1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw1.dir/clean

CMakeFiles/hw1.dir/depend:
	cd /home/gordonchan/codes/cs111_spring2019/hw1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gordonchan/codes/cs111_spring2019/hw1 /home/gordonchan/codes/cs111_spring2019/hw1 /home/gordonchan/codes/cs111_spring2019/hw1 /home/gordonchan/codes/cs111_spring2019/hw1 /home/gordonchan/codes/cs111_spring2019/hw1/CMakeFiles/hw1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw1.dir/depend

