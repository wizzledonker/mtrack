# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/win/Documents/Development/Personal/mtrack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/win/Documents/Development/Personal/mtrack

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/win/Documents/Development/Personal/mtrack/CMakeFiles /home/win/Documents/Development/Personal/mtrack/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/win/Documents/Development/Personal/mtrack/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named mtrack

# Build rule for target.
mtrack: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 mtrack
.PHONY : mtrack

# fast build rule for target.
mtrack/fast:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/build
.PHONY : mtrack/fast

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/render/cmanager.o: src/render/cmanager.cpp.o

.PHONY : src/render/cmanager.o

# target to build an object file
src/render/cmanager.cpp.o:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/render/cmanager.cpp.o
.PHONY : src/render/cmanager.cpp.o

src/render/cmanager.i: src/render/cmanager.cpp.i

.PHONY : src/render/cmanager.i

# target to preprocess a source file
src/render/cmanager.cpp.i:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/render/cmanager.cpp.i
.PHONY : src/render/cmanager.cpp.i

src/render/cmanager.s: src/render/cmanager.cpp.s

.PHONY : src/render/cmanager.s

# target to generate assembly for a file
src/render/cmanager.cpp.s:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/render/cmanager.cpp.s
.PHONY : src/render/cmanager.cpp.s

src/ui/main_window.o: src/ui/main_window.cpp.o

.PHONY : src/ui/main_window.o

# target to build an object file
src/ui/main_window.cpp.o:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/ui/main_window.cpp.o
.PHONY : src/ui/main_window.cpp.o

src/ui/main_window.i: src/ui/main_window.cpp.i

.PHONY : src/ui/main_window.i

# target to preprocess a source file
src/ui/main_window.cpp.i:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/ui/main_window.cpp.i
.PHONY : src/ui/main_window.cpp.i

src/ui/main_window.s: src/ui/main_window.cpp.s

.PHONY : src/ui/main_window.s

# target to generate assembly for a file
src/ui/main_window.cpp.s:
	$(MAKE) -f CMakeFiles/mtrack.dir/build.make CMakeFiles/mtrack.dir/src/ui/main_window.cpp.s
.PHONY : src/ui/main_window.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... mtrack"
	@echo "... edit_cache"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/render/cmanager.o"
	@echo "... src/render/cmanager.i"
	@echo "... src/render/cmanager.s"
	@echo "... src/ui/main_window.o"
	@echo "... src/ui/main_window.i"
	@echo "... src/ui/main_window.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

