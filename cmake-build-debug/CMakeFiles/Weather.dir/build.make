# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files\JetBrains\CLion 2020.3.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\20304\Documents\Weather

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\20304\Documents\Weather\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Weather.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Weather.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Weather.dir/flags.make

CMakeFiles/Weather.dir/cJSON.c.obj: CMakeFiles/Weather.dir/flags.make
CMakeFiles/Weather.dir/cJSON.c.obj: ../cJSON.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\20304\Documents\Weather\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Weather.dir/cJSON.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Weather.dir\cJSON.c.obj   -c C:\Users\20304\Documents\Weather\cJSON.c

CMakeFiles/Weather.dir/cJSON.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Weather.dir/cJSON.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\20304\Documents\Weather\cJSON.c > CMakeFiles\Weather.dir\cJSON.c.i

CMakeFiles/Weather.dir/cJSON.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Weather.dir/cJSON.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\20304\Documents\Weather\cJSON.c -o CMakeFiles\Weather.dir\cJSON.c.s

CMakeFiles/Weather.dir/main.cpp.obj: CMakeFiles/Weather.dir/flags.make
CMakeFiles/Weather.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\20304\Documents\Weather\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Weather.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Weather.dir\main.cpp.obj -c C:\Users\20304\Documents\Weather\main.cpp

CMakeFiles/Weather.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Weather.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\20304\Documents\Weather\main.cpp > CMakeFiles\Weather.dir\main.cpp.i

CMakeFiles/Weather.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Weather.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\20304\Documents\Weather\main.cpp -o CMakeFiles\Weather.dir\main.cpp.s

CMakeFiles/Weather.dir/utf8togbk.c.obj: CMakeFiles/Weather.dir/flags.make
CMakeFiles/Weather.dir/utf8togbk.c.obj: ../utf8togbk.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\20304\Documents\Weather\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Weather.dir/utf8togbk.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Weather.dir\utf8togbk.c.obj   -c C:\Users\20304\Documents\Weather\utf8togbk.c

CMakeFiles/Weather.dir/utf8togbk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Weather.dir/utf8togbk.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\20304\Documents\Weather\utf8togbk.c > CMakeFiles\Weather.dir\utf8togbk.c.i

CMakeFiles/Weather.dir/utf8togbk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Weather.dir/utf8togbk.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\20304\Documents\Weather\utf8togbk.c -o CMakeFiles\Weather.dir\utf8togbk.c.s

# Object files for target Weather
Weather_OBJECTS = \
"CMakeFiles/Weather.dir/cJSON.c.obj" \
"CMakeFiles/Weather.dir/main.cpp.obj" \
"CMakeFiles/Weather.dir/utf8togbk.c.obj"

# External object files for target Weather
Weather_EXTERNAL_OBJECTS =

Weather.exe: CMakeFiles/Weather.dir/cJSON.c.obj
Weather.exe: CMakeFiles/Weather.dir/main.cpp.obj
Weather.exe: CMakeFiles/Weather.dir/utf8togbk.c.obj
Weather.exe: CMakeFiles/Weather.dir/build.make
Weather.exe: C:/MinGW/lib/libwsock32.a
Weather.exe: CMakeFiles/Weather.dir/objects1.rsp
Weather.exe: CMakeFiles/Weather.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\20304\Documents\Weather\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Weather.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Weather.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Weather.dir/build: Weather.exe

.PHONY : CMakeFiles/Weather.dir/build

CMakeFiles/Weather.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Weather.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Weather.dir/clean

CMakeFiles/Weather.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\20304\Documents\Weather C:\Users\20304\Documents\Weather C:\Users\20304\Documents\Weather\cmake-build-debug C:\Users\20304\Documents\Weather\cmake-build-debug C:\Users\20304\Documents\Weather\cmake-build-debug\CMakeFiles\Weather.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Weather.dir/depend

