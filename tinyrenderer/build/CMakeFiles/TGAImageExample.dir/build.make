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
CMAKE_SOURCE_DIR = /home/ori/code/cpp/tiny/tinyrenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ori/code/cpp/tiny/tinyrenderer/build

# Include any dependencies generated for this target.
include CMakeFiles/TGAImageExample.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TGAImageExample.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TGAImageExample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TGAImageExample.dir/flags.make

CMakeFiles/TGAImageExample.dir/main.cpp.o: CMakeFiles/TGAImageExample.dir/flags.make
CMakeFiles/TGAImageExample.dir/main.cpp.o: ../main.cpp
CMakeFiles/TGAImageExample.dir/main.cpp.o: CMakeFiles/TGAImageExample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ori/code/cpp/tiny/tinyrenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TGAImageExample.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TGAImageExample.dir/main.cpp.o -MF CMakeFiles/TGAImageExample.dir/main.cpp.o.d -o CMakeFiles/TGAImageExample.dir/main.cpp.o -c /home/ori/code/cpp/tiny/tinyrenderer/main.cpp

CMakeFiles/TGAImageExample.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TGAImageExample.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ori/code/cpp/tiny/tinyrenderer/main.cpp > CMakeFiles/TGAImageExample.dir/main.cpp.i

CMakeFiles/TGAImageExample.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TGAImageExample.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ori/code/cpp/tiny/tinyrenderer/main.cpp -o CMakeFiles/TGAImageExample.dir/main.cpp.s

CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o: CMakeFiles/TGAImageExample.dir/flags.make
CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o: ../tgaimage.cpp
CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o: CMakeFiles/TGAImageExample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ori/code/cpp/tiny/tinyrenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o -MF CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o.d -o CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o -c /home/ori/code/cpp/tiny/tinyrenderer/tgaimage.cpp

CMakeFiles/TGAImageExample.dir/tgaimage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TGAImageExample.dir/tgaimage.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ori/code/cpp/tiny/tinyrenderer/tgaimage.cpp > CMakeFiles/TGAImageExample.dir/tgaimage.cpp.i

CMakeFiles/TGAImageExample.dir/tgaimage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TGAImageExample.dir/tgaimage.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ori/code/cpp/tiny/tinyrenderer/tgaimage.cpp -o CMakeFiles/TGAImageExample.dir/tgaimage.cpp.s

# Object files for target TGAImageExample
TGAImageExample_OBJECTS = \
"CMakeFiles/TGAImageExample.dir/main.cpp.o" \
"CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o"

# External object files for target TGAImageExample
TGAImageExample_EXTERNAL_OBJECTS =

TGAImageExample: CMakeFiles/TGAImageExample.dir/main.cpp.o
TGAImageExample: CMakeFiles/TGAImageExample.dir/tgaimage.cpp.o
TGAImageExample: CMakeFiles/TGAImageExample.dir/build.make
TGAImageExample: CMakeFiles/TGAImageExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ori/code/cpp/tiny/tinyrenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable TGAImageExample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TGAImageExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TGAImageExample.dir/build: TGAImageExample
.PHONY : CMakeFiles/TGAImageExample.dir/build

CMakeFiles/TGAImageExample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TGAImageExample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TGAImageExample.dir/clean

CMakeFiles/TGAImageExample.dir/depend:
	cd /home/ori/code/cpp/tiny/tinyrenderer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ori/code/cpp/tiny/tinyrenderer /home/ori/code/cpp/tiny/tinyrenderer /home/ori/code/cpp/tiny/tinyrenderer/build /home/ori/code/cpp/tiny/tinyrenderer/build /home/ori/code/cpp/tiny/tinyrenderer/build/CMakeFiles/TGAImageExample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TGAImageExample.dir/depend

