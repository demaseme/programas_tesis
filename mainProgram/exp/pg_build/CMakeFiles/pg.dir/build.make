# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build

# Include any dependencies generated for this target.
include CMakeFiles/pg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pg.dir/flags.make

CMakeFiles/pg.dir/point_generator.cpp.o: CMakeFiles/pg.dir/flags.make
CMakeFiles/pg.dir/point_generator.cpp.o: ../point_generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pg.dir/point_generator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pg.dir/point_generator.cpp.o -c /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/point_generator.cpp

CMakeFiles/pg.dir/point_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pg.dir/point_generator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/point_generator.cpp > CMakeFiles/pg.dir/point_generator.cpp.i

CMakeFiles/pg.dir/point_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pg.dir/point_generator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/point_generator.cpp -o CMakeFiles/pg.dir/point_generator.cpp.s

CMakeFiles/pg.dir/point_generator.cpp.o.requires:

.PHONY : CMakeFiles/pg.dir/point_generator.cpp.o.requires

CMakeFiles/pg.dir/point_generator.cpp.o.provides: CMakeFiles/pg.dir/point_generator.cpp.o.requires
	$(MAKE) -f CMakeFiles/pg.dir/build.make CMakeFiles/pg.dir/point_generator.cpp.o.provides.build
.PHONY : CMakeFiles/pg.dir/point_generator.cpp.o.provides

CMakeFiles/pg.dir/point_generator.cpp.o.provides.build: CMakeFiles/pg.dir/point_generator.cpp.o


# Object files for target pg
pg_OBJECTS = \
"CMakeFiles/pg.dir/point_generator.cpp.o"

# External object files for target pg
pg_EXTERNAL_OBJECTS =

pg: CMakeFiles/pg.dir/point_generator.cpp.o
pg: CMakeFiles/pg.dir/build.make
pg: /usr/lib/x86_64-linux-gnu/libmpfr.so
pg: /usr/lib/x86_64-linux-gnu/libgmpxx.so
pg: /usr/lib/x86_64-linux-gnu/libgmp.so
pg: /usr/lib/x86_64-linux-gnu/libCGAL.so.13.0.1
pg: /usr/lib/x86_64-linux-gnu/libCGAL.so.13.0.1
pg: CMakeFiles/pg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pg"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pg.dir/build: pg

.PHONY : CMakeFiles/pg.dir/build

CMakeFiles/pg.dir/requires: CMakeFiles/pg.dir/point_generator.cpp.o.requires

.PHONY : CMakeFiles/pg.dir/requires

CMakeFiles/pg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pg.dir/clean

CMakeFiles/pg.dir/depend:
	cd /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build /home/dmerinos/Documents/CINVESTAV/Tesis/programas_tesis/mainProgram/exp/pg_build/CMakeFiles/pg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pg.dir/depend

