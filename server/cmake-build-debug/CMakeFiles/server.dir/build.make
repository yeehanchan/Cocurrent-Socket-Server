# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/yeehanchen/clion/clion-2016.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/yeehanchen/clion/clion-2016.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/yeehanchen/workspace/network&dis/project-1/server"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/server.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server.dir/server.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/server.c.o   -c "/home/yeehanchen/workspace/network&dis/project-1/server/server.c"

CMakeFiles/server.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/server.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/yeehanchen/workspace/network&dis/project-1/server/server.c" > CMakeFiles/server.dir/server.c.i

CMakeFiles/server.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/server.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/yeehanchen/workspace/network&dis/project-1/server/server.c" -o CMakeFiles/server.dir/server.c.s

CMakeFiles/server.dir/server.c.o.requires:

.PHONY : CMakeFiles/server.dir/server.c.o.requires

CMakeFiles/server.dir/server.c.o.provides: CMakeFiles/server.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/server.c.o.provides.build
.PHONY : CMakeFiles/server.dir/server.c.o.provides

CMakeFiles/server.dir/server.c.o.provides.build: CMakeFiles/server.dir/server.c.o


CMakeFiles/server.dir/parse.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/parse.c.o: ../parse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server.dir/parse.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/parse.c.o   -c "/home/yeehanchen/workspace/network&dis/project-1/server/parse.c"

CMakeFiles/server.dir/parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/parse.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/yeehanchen/workspace/network&dis/project-1/server/parse.c" > CMakeFiles/server.dir/parse.c.i

CMakeFiles/server.dir/parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/parse.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/yeehanchen/workspace/network&dis/project-1/server/parse.c" -o CMakeFiles/server.dir/parse.c.s

CMakeFiles/server.dir/parse.c.o.requires:

.PHONY : CMakeFiles/server.dir/parse.c.o.requires

CMakeFiles/server.dir/parse.c.o.provides: CMakeFiles/server.dir/parse.c.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/parse.c.o.provides.build
.PHONY : CMakeFiles/server.dir/parse.c.o.provides

CMakeFiles/server.dir/parse.c.o.provides.build: CMakeFiles/server.dir/parse.c.o


CMakeFiles/server.dir/y.tab.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/y.tab.c.o: ../y.tab.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/y.tab.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/y.tab.c.o   -c "/home/yeehanchen/workspace/network&dis/project-1/server/y.tab.c"

CMakeFiles/server.dir/y.tab.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/y.tab.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/yeehanchen/workspace/network&dis/project-1/server/y.tab.c" > CMakeFiles/server.dir/y.tab.c.i

CMakeFiles/server.dir/y.tab.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/y.tab.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/yeehanchen/workspace/network&dis/project-1/server/y.tab.c" -o CMakeFiles/server.dir/y.tab.c.s

CMakeFiles/server.dir/y.tab.c.o.requires:

.PHONY : CMakeFiles/server.dir/y.tab.c.o.requires

CMakeFiles/server.dir/y.tab.c.o.provides: CMakeFiles/server.dir/y.tab.c.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/y.tab.c.o.provides.build
.PHONY : CMakeFiles/server.dir/y.tab.c.o.provides

CMakeFiles/server.dir/y.tab.c.o.provides.build: CMakeFiles/server.dir/y.tab.c.o


CMakeFiles/server.dir/lex.yy.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/lex.yy.c.o: ../lex.yy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/server.dir/lex.yy.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/lex.yy.c.o   -c "/home/yeehanchen/workspace/network&dis/project-1/server/lex.yy.c"

CMakeFiles/server.dir/lex.yy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/lex.yy.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/yeehanchen/workspace/network&dis/project-1/server/lex.yy.c" > CMakeFiles/server.dir/lex.yy.c.i

CMakeFiles/server.dir/lex.yy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/lex.yy.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/yeehanchen/workspace/network&dis/project-1/server/lex.yy.c" -o CMakeFiles/server.dir/lex.yy.c.s

CMakeFiles/server.dir/lex.yy.c.o.requires:

.PHONY : CMakeFiles/server.dir/lex.yy.c.o.requires

CMakeFiles/server.dir/lex.yy.c.o.provides: CMakeFiles/server.dir/lex.yy.c.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/lex.yy.c.o.provides.build
.PHONY : CMakeFiles/server.dir/lex.yy.c.o.provides

CMakeFiles/server.dir/lex.yy.c.o.provides.build: CMakeFiles/server.dir/lex.yy.c.o


CMakeFiles/server.dir/httpResponse.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/httpResponse.c.o: ../httpResponse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/server.dir/httpResponse.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/server.dir/httpResponse.c.o   -c "/home/yeehanchen/workspace/network&dis/project-1/server/httpResponse.c"

CMakeFiles/server.dir/httpResponse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/httpResponse.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/yeehanchen/workspace/network&dis/project-1/server/httpResponse.c" > CMakeFiles/server.dir/httpResponse.c.i

CMakeFiles/server.dir/httpResponse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/httpResponse.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/yeehanchen/workspace/network&dis/project-1/server/httpResponse.c" -o CMakeFiles/server.dir/httpResponse.c.s

CMakeFiles/server.dir/httpResponse.c.o.requires:

.PHONY : CMakeFiles/server.dir/httpResponse.c.o.requires

CMakeFiles/server.dir/httpResponse.c.o.provides: CMakeFiles/server.dir/httpResponse.c.o.requires
	$(MAKE) -f CMakeFiles/server.dir/build.make CMakeFiles/server.dir/httpResponse.c.o.provides.build
.PHONY : CMakeFiles/server.dir/httpResponse.c.o.provides

CMakeFiles/server.dir/httpResponse.c.o.provides.build: CMakeFiles/server.dir/httpResponse.c.o


# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server.c.o" \
"CMakeFiles/server.dir/parse.c.o" \
"CMakeFiles/server.dir/y.tab.c.o" \
"CMakeFiles/server.dir/lex.yy.c.o" \
"CMakeFiles/server.dir/httpResponse.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server.c.o
server: CMakeFiles/server.dir/parse.c.o
server: CMakeFiles/server.dir/y.tab.c.o
server: CMakeFiles/server.dir/lex.yy.c.o
server: CMakeFiles/server.dir/httpResponse.c.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/requires: CMakeFiles/server.dir/server.c.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/parse.c.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/y.tab.c.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/lex.yy.c.o.requires
CMakeFiles/server.dir/requires: CMakeFiles/server.dir/httpResponse.c.o.requires

.PHONY : CMakeFiles/server.dir/requires

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd "/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/yeehanchen/workspace/network&dis/project-1/server" "/home/yeehanchen/workspace/network&dis/project-1/server" "/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug" "/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug" "/home/yeehanchen/workspace/network&dis/project-1/server/cmake-build-debug/CMakeFiles/server.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

