# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonnydepp/programming/vita/csvita2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonnydepp/programming/vita/csvita2

# Utility rule file for csvita.vpk.

# Include the progress variables for this target.
include CMakeFiles/csvita.vpk.dir/progress.make

CMakeFiles/csvita.vpk: csvita.vpk_param.sfo
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonnydepp/programming/vita/csvita2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building vpk csvita.vpk"
	/usr/local/vitasdk/bin/vita-pack-vpk -a /home/jonnydepp/programming/vita/csvita2/sce_sys/icon0.png=sce_sys/icon0.png -a /home/jonnydepp/programming/vita/csvita2/sce_sys/livearea/contents/bg.png=sce_sys/livearea/contents/bg.png -a /home/jonnydepp/programming/vita/csvita2/sce_sys/livearea/contents/startup.png=sce_sys/livearea/contents/startup.png -a /home/jonnydepp/programming/vita/csvita2/sce_sys/livearea/contents/template.xml=sce_sys/livearea/contents/template.xml -a /home/jonnydepp/programming/vita/csvita2/images/player.png=images/player.png -a /home/jonnydepp/programming/vita/csvita2/images/csmenubackground.png=images/csmenubackground.png -s csvita.vpk_param.sfo -b csvita.self csvita.vpk

csvita.vpk_param.sfo:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/jonnydepp/programming/vita/csvita2/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating param.sfo for csvita.vpk"
	/usr/local/vitasdk/bin/vita-mksfoex -d PARENTAL_LEVEL=1 -s APP_VER=13.37 -s TITLE_ID=CSVT01337 CS2dVITA csvita.vpk_param.sfo

csvita.vpk: CMakeFiles/csvita.vpk
csvita.vpk: csvita.vpk_param.sfo
csvita.vpk: CMakeFiles/csvita.vpk.dir/build.make

.PHONY : csvita.vpk

# Rule to build all files generated by this target.
CMakeFiles/csvita.vpk.dir/build: csvita.vpk

.PHONY : CMakeFiles/csvita.vpk.dir/build

CMakeFiles/csvita.vpk.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/csvita.vpk.dir/cmake_clean.cmake
.PHONY : CMakeFiles/csvita.vpk.dir/clean

CMakeFiles/csvita.vpk.dir/depend:
	cd /home/jonnydepp/programming/vita/csvita2 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonnydepp/programming/vita/csvita2 /home/jonnydepp/programming/vita/csvita2 /home/jonnydepp/programming/vita/csvita2 /home/jonnydepp/programming/vita/csvita2 /home/jonnydepp/programming/vita/csvita2/CMakeFiles/csvita.vpk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/csvita.vpk.dir/depend

