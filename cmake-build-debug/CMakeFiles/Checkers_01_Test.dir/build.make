# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_BINARY_DIR = C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Checkers_01_Test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Checkers_01_Test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Checkers_01_Test.dir/flags.make

CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.obj: ../src/main/POCO/Checker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\POCO\Checker.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\POCO\Checker.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\POCO\Checker.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\POCO\Checker.i

CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\POCO\Checker.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\POCO\Checker.s

CMakeFiles/Checkers_01_Test.dir/src/main/Board.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/Board.obj: ../src/main/Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/Board.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\Board.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\Board.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/Board.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/Board.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\Board.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\Board.i

CMakeFiles/Checkers_01_Test.dir/src/main/Board.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/Board.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\Board.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\Board.s

CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.obj: ../src/main/human/Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\human\Parser.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\human\Parser.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\human\Parser.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\human\Parser.i

CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\human\Parser.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\human\Parser.s

CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.obj: ../src/main/POCO/Move.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\POCO\Move.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\POCO\Move.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\POCO\Move.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\POCO\Move.i

CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\POCO\Move.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\POCO\Move.s

CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.obj: ../src/main/GameManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\GameManager.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\GameManager.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\GameManager.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\GameManager.i

CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\GameManager.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\GameManager.s

CMakeFiles/Checkers_01_Test.dir/src/main/Rules.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/Rules.obj: ../src/main/Rules.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/Rules.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\Rules.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\Rules.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/Rules.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/Rules.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\Rules.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\Rules.i

CMakeFiles/Checkers_01_Test.dir/src/main/Rules.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/Rules.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\Rules.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\Rules.s

CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.obj: ../src/main/AI/AI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\AI\AI.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\AI.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\AI.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\AI\AI.i

CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\AI.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\AI\AI.s

CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.obj: ../src/main/AI/Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\AI\Node.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\Node.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\Node.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\AI\Node.i

CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\Node.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\AI\Node.s

CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.obj: ../src/main/AI/MinimaxTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\main\AI\MinimaxTree.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\MinimaxTree.cpp

CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\MinimaxTree.cpp > CMakeFiles\Checkers_01_Test.dir\src\main\AI\MinimaxTree.i

CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\main\AI\MinimaxTree.cpp -o CMakeFiles\Checkers_01_Test.dir\src\main\AI\MinimaxTree.s

CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.obj: ../src/test/tests-Board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\test\tests-Board.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\test\tests-Board.cpp

CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\test\tests-Board.cpp > CMakeFiles\Checkers_01_Test.dir\src\test\tests-Board.i

CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\test\tests-Board.cpp -o CMakeFiles\Checkers_01_Test.dir\src\test\tests-Board.s

CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.obj: CMakeFiles/Checkers_01_Test.dir/flags.make
CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.obj: ../src/test/tests-main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Checkers_01_Test.dir\src\test\tests-main.obj -c C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\test\tests-main.cpp

CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\test\tests-main.cpp > CMakeFiles\Checkers_01_Test.dir\src\test\tests-main.i

CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\src\test\tests-main.cpp -o CMakeFiles\Checkers_01_Test.dir\src\test\tests-main.s

# Object files for target Checkers_01_Test
Checkers_01_Test_OBJECTS = \
"CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/Board.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/Rules.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.obj" \
"CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.obj"

# External object files for target Checkers_01_Test
Checkers_01_Test_EXTERNAL_OBJECTS =

Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Checker.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/Board.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/human/Parser.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/POCO/Move.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/GameManager.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/Rules.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/AI/AI.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/AI/Node.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/main/AI/MinimaxTree.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/test/tests-Board.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/src/test/tests-main.obj
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/build.make
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/linklibs.rsp
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/objects1.rsp
Checkers_01_Test.exe: CMakeFiles/Checkers_01_Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable Checkers_01_Test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Checkers_01_Test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Checkers_01_Test.dir/build: Checkers_01_Test.exe

.PHONY : CMakeFiles/Checkers_01_Test.dir/build

CMakeFiles/Checkers_01_Test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Checkers_01_Test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Checkers_01_Test.dir/clean

CMakeFiles/Checkers_01_Test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Luke\CLionProjects\Minimax-AI-Checkers C:\Users\Luke\CLionProjects\Minimax-AI-Checkers C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug C:\Users\Luke\CLionProjects\Minimax-AI-Checkers\cmake-build-debug\CMakeFiles\Checkers_01_Test.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Checkers_01_Test.dir/depend

