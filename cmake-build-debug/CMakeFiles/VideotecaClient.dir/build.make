# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/81/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/81/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tiziana/CLionProjects/VideotecaClient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/VideotecaClient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VideotecaClient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VideotecaClient.dir/flags.make

CMakeFiles/VideotecaClient.dir/main.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/VideotecaClient.dir/main.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/main.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/main.c

CMakeFiles/VideotecaClient.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/main.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/main.c > CMakeFiles/VideotecaClient.dir/main.c.i

CMakeFiles/VideotecaClient.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/main.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/main.c -o CMakeFiles/VideotecaClient.dir/main.c.s

CMakeFiles/VideotecaClient.dir/jsmn.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/jsmn.c.o: ../jsmn.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/VideotecaClient.dir/jsmn.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/jsmn.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/jsmn.c

CMakeFiles/VideotecaClient.dir/jsmn.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/jsmn.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/jsmn.c > CMakeFiles/VideotecaClient.dir/jsmn.c.i

CMakeFiles/VideotecaClient.dir/jsmn.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/jsmn.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/jsmn.c -o CMakeFiles/VideotecaClient.dir/jsmn.c.s

CMakeFiles/VideotecaClient.dir/inout.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/inout.c.o: ../inout.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/VideotecaClient.dir/inout.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/inout.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/inout.c

CMakeFiles/VideotecaClient.dir/inout.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/inout.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/inout.c > CMakeFiles/VideotecaClient.dir/inout.c.i

CMakeFiles/VideotecaClient.dir/inout.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/inout.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/inout.c -o CMakeFiles/VideotecaClient.dir/inout.c.s

CMakeFiles/VideotecaClient.dir/parse.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/parse.c.o: ../parse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/VideotecaClient.dir/parse.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/parse.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/parse.c

CMakeFiles/VideotecaClient.dir/parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/parse.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/parse.c > CMakeFiles/VideotecaClient.dir/parse.c.i

CMakeFiles/VideotecaClient.dir/parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/parse.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/parse.c -o CMakeFiles/VideotecaClient.dir/parse.c.s

CMakeFiles/VideotecaClient.dir/utils.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/utils.c.o: ../utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/VideotecaClient.dir/utils.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/utils.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/utils.c

CMakeFiles/VideotecaClient.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/utils.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/utils.c > CMakeFiles/VideotecaClient.dir/utils.c.i

CMakeFiles/VideotecaClient.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/utils.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/utils.c -o CMakeFiles/VideotecaClient.dir/utils.c.s

CMakeFiles/VideotecaClient.dir/cliente.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/cliente.c.o: ../cliente.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/VideotecaClient.dir/cliente.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/cliente.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/cliente.c

CMakeFiles/VideotecaClient.dir/cliente.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/cliente.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/cliente.c > CMakeFiles/VideotecaClient.dir/cliente.c.i

CMakeFiles/VideotecaClient.dir/cliente.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/cliente.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/cliente.c -o CMakeFiles/VideotecaClient.dir/cliente.c.s

CMakeFiles/VideotecaClient.dir/manager.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/manager.c.o: ../manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/VideotecaClient.dir/manager.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/manager.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/manager.c

CMakeFiles/VideotecaClient.dir/manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/manager.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/manager.c > CMakeFiles/VideotecaClient.dir/manager.c.i

CMakeFiles/VideotecaClient.dir/manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/manager.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/manager.c -o CMakeFiles/VideotecaClient.dir/manager.c.s

CMakeFiles/VideotecaClient.dir/impiegato.c.o: CMakeFiles/VideotecaClient.dir/flags.make
CMakeFiles/VideotecaClient.dir/impiegato.c.o: ../impiegato.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/VideotecaClient.dir/impiegato.c.o"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/VideotecaClient.dir/impiegato.c.o   -c /home/tiziana/CLionProjects/VideotecaClient/impiegato.c

CMakeFiles/VideotecaClient.dir/impiegato.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/VideotecaClient.dir/impiegato.c.i"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tiziana/CLionProjects/VideotecaClient/impiegato.c > CMakeFiles/VideotecaClient.dir/impiegato.c.i

CMakeFiles/VideotecaClient.dir/impiegato.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/VideotecaClient.dir/impiegato.c.s"
	/usr/bin/gcc-8 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tiziana/CLionProjects/VideotecaClient/impiegato.c -o CMakeFiles/VideotecaClient.dir/impiegato.c.s

# Object files for target VideotecaClient
VideotecaClient_OBJECTS = \
"CMakeFiles/VideotecaClient.dir/main.c.o" \
"CMakeFiles/VideotecaClient.dir/jsmn.c.o" \
"CMakeFiles/VideotecaClient.dir/inout.c.o" \
"CMakeFiles/VideotecaClient.dir/parse.c.o" \
"CMakeFiles/VideotecaClient.dir/utils.c.o" \
"CMakeFiles/VideotecaClient.dir/cliente.c.o" \
"CMakeFiles/VideotecaClient.dir/manager.c.o" \
"CMakeFiles/VideotecaClient.dir/impiegato.c.o"

# External object files for target VideotecaClient
VideotecaClient_EXTERNAL_OBJECTS =

VideotecaClient: CMakeFiles/VideotecaClient.dir/main.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/jsmn.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/inout.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/parse.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/utils.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/cliente.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/manager.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/impiegato.c.o
VideotecaClient: CMakeFiles/VideotecaClient.dir/build.make
VideotecaClient: CMakeFiles/VideotecaClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable VideotecaClient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VideotecaClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VideotecaClient.dir/build: VideotecaClient

.PHONY : CMakeFiles/VideotecaClient.dir/build

CMakeFiles/VideotecaClient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VideotecaClient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VideotecaClient.dir/clean

CMakeFiles/VideotecaClient.dir/depend:
	cd /home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tiziana/CLionProjects/VideotecaClient /home/tiziana/CLionProjects/VideotecaClient /home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug /home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug /home/tiziana/CLionProjects/VideotecaClient/cmake-build-debug/CMakeFiles/VideotecaClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VideotecaClient.dir/depend

