# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Luke\CLionProjects\Minimax-AI-Checkers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Luke\CLionProjects\Minimax-AI-Checkers

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -E echo "No interactive CMake dialog available."
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\JetBrains\CLion 2018.3.3\bin\cmake\win\bin\cmake.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\CMakeFiles C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\CMakeFiles\progress.marks
	$(MAKE) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Checkers_01

# Build rule for target.
Checkers_01: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 Checkers_01
.PHONY : Checkers_01

# fast build rule for target.
Checkers_01/fast:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/build
.PHONY : Checkers_01/fast

#=============================================================================
# Target rules for targets named Checkers_01_Test

# Build rule for target.
Checkers_01_Test: cmake_check_build_system
	$(MAKE) -f CMakeFiles\Makefile2 Checkers_01_Test
.PHONY : Checkers_01_Test

# fast build rule for target.
Checkers_01_Test/fast:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/build
.PHONY : Checkers_01_Test/fast

# target to build an object file
src/main/AI/AI.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/AI.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.obj
.PHONY : src/main/AI/AI.obj

# target to preprocess a source file
src/main/AI/AI.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/AI.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.i
.PHONY : src/main/AI/AI.i

# target to generate assembly for a file
src/main/AI/AI.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/AI.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.s
.PHONY : src/main/AI/AI.s

# target to build an object file
src/main/AI/MinimaxTree.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/MinimaxTree.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.obj
.PHONY : src/main/AI/MinimaxTree.obj

# target to preprocess a source file
src/main/AI/MinimaxTree.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/MinimaxTree.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.i
.PHONY : src/main/AI/MinimaxTree.i

# target to generate assembly for a file
src/main/AI/MinimaxTree.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/MinimaxTree.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.s
.PHONY : src/main/AI/MinimaxTree.s

# target to build an object file
src/main/AI/Node.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/Node.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.obj
.PHONY : src/main/AI/Node.obj

# target to preprocess a source file
src/main/AI/Node.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/Node.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.i
.PHONY : src/main/AI/Node.i

# target to generate assembly for a file
src/main/AI/Node.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/AI/Node.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.s
.PHONY : src/main/AI/Node.s

# target to build an object file
src/main/Board.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/Board.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/Board.obj
.PHONY : src/main/Board.obj

# target to preprocess a source file
src/main/Board.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/Board.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/Board.i
.PHONY : src/main/Board.i

# target to generate assembly for a file
src/main/Board.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/Board.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/Board.s
.PHONY : src/main/Board.s

# target to build an object file
src/main/GameManager.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/GameManager.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.obj
.PHONY : src/main/GameManager.obj

# target to preprocess a source file
src/main/GameManager.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/GameManager.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.i
.PHONY : src/main/GameManager.i

# target to generate assembly for a file
src/main/GameManager.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/GameManager.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.s
.PHONY : src/main/GameManager.s

# target to build an object file
src/main/POCO/Checker.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/POCO/Checker.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.obj
.PHONY : src/main/POCO/Checker.obj

# target to preprocess a source file
src/main/POCO/Checker.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/POCO/Checker.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.i
.PHONY : src/main/POCO/Checker.i

# target to generate assembly for a file
src/main/POCO/Checker.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/POCO/Checker.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.s
.PHONY : src/main/POCO/Checker.s

# target to build an object file
src/main/POCO/Move.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/POCO/Move.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.obj
.PHONY : src/main/POCO/Move.obj

# target to preprocess a source file
src/main/POCO/Move.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/POCO/Move.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.i
.PHONY : src/main/POCO/Move.i

# target to generate assembly for a file
src/main/POCO/Move.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/POCO/Move.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.s
.PHONY : src/main/POCO/Move.s

# target to build an object file
src/main/Rules.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/Rules.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/Rules.obj
.PHONY : src/main/Rules.obj

# target to preprocess a source file
src/main/Rules.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/Rules.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/Rules.i
.PHONY : src/main/Rules.i

# target to generate assembly for a file
src/main/Rules.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/Rules.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/Rules.s
.PHONY : src/main/Rules.s

# target to build an object file
src/main/human/Parser.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/human/Parser.obj
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.obj
.PHONY : src/main/human/Parser.obj

# target to preprocess a source file
src/main/human/Parser.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/human/Parser.i
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.i
.PHONY : src/main/human/Parser.i

# target to generate assembly for a file
src/main/human/Parser.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/human/Parser.s
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.s
.PHONY : src/main/human/Parser.s

# target to build an object file
src/main/main.obj:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/main.obj
.PHONY : src/main/main.obj

# target to preprocess a source file
src/main/main.i:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/main.i
.PHONY : src/main/main.i

# target to generate assembly for a file
src/main/main.s:
	$(MAKE) -f CMakeFiles\Checkers_01.dir\build.make CMakeFiles/Checkers_01.dir/src/main/main.s
.PHONY : src/main/main.s

# target to build an object file
src/test/tests-Board.obj:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.obj
.PHONY : src/test/tests-Board.obj

# target to preprocess a source file
src/test/tests-Board.i:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.i
.PHONY : src/test/tests-Board.i

# target to generate assembly for a file
src/test/tests-Board.s:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.s
.PHONY : src/test/tests-Board.s

# target to build an object file
src/test/tests-main.obj:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.obj
.PHONY : src/test/tests-main.obj

# target to preprocess a source file
src/test/tests-main.i:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.i
.PHONY : src/test/tests-main.i

# target to generate assembly for a file
src/test/tests-main.s:
	$(MAKE) -f CMakeFiles\Checkers_01_Test.dir\build.make CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.s
.PHONY : src/test/tests-main.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... Checkers_01
	@echo ... Checkers_01_Test
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... src/main/AI/AI.obj
	@echo ... src/main/AI/AI.i
	@echo ... src/main/AI/AI.s
	@echo ... src/main/AI/MinimaxTree.obj
	@echo ... src/main/AI/MinimaxTree.i
	@echo ... src/main/AI/MinimaxTree.s
	@echo ... src/main/AI/Node.obj
	@echo ... src/main/AI/Node.i
	@echo ... src/main/AI/Node.s
	@echo ... src/main/Board.obj
	@echo ... src/main/Board.i
	@echo ... src/main/Board.s
	@echo ... src/main/GameManager.obj
	@echo ... src/main/GameManager.i
	@echo ... src/main/GameManager.s
	@echo ... src/main/POCO/Checker.obj
	@echo ... src/main/POCO/Checker.i
	@echo ... src/main/POCO/Checker.s
	@echo ... src/main/POCO/Move.obj
	@echo ... src/main/POCO/Move.i
	@echo ... src/main/POCO/Move.s
	@echo ... src/main/Rules.obj
	@echo ... src/main/Rules.i
	@echo ... src/main/Rules.s
	@echo ... src/main/human/Parser.obj
	@echo ... src/main/human/Parser.i
	@echo ... src/main/human/Parser.s
	@echo ... src/main/main.obj
	@echo ... src/main/main.i
	@echo ... src/main/main.s
	@echo ... src/test/tests-Board.obj
	@echo ... src/test/tests-Board.i
	@echo ... src/test/tests-Board.s
	@echo ... src/test/tests-main.obj
	@echo ... src/test/tests-main.i
	@echo ... src/test/tests-main.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

