# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/tom/Epitech/RType/R-Type-Revival

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom/Epitech/RType/R-Type-Revival/server

# Include any dependencies generated for this target.
include server/CMakeFiles/r-type_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server/CMakeFiles/r-type_server.dir/compiler_depend.make

# Include the progress variables for this target.
include server/CMakeFiles/r-type_server.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/r-type_server.dir/flags.make

server/CMakeFiles/r-type_server.dir/src/main.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/main.cpp.o: src/main.cpp
server/CMakeFiles/r-type_server.dir/src/main.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/CMakeFiles/r-type_server.dir/src/main.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/main.cpp.o -MF CMakeFiles/r-type_server.dir/src/main.cpp.o.d -o CMakeFiles/r-type_server.dir/src/main.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/main.cpp

server/CMakeFiles/r-type_server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/main.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/main.cpp > CMakeFiles/r-type_server.dir/src/main.cpp.i

server/CMakeFiles/r-type_server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/main.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/main.cpp -o CMakeFiles/r-type_server.dir/src/main.cpp.s

server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o: src/managers/entity_manager.cpp
server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o -MF CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o.d -o CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/entity_manager.cpp

server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/entity_manager.cpp > CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.i

server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/entity_manager.cpp -o CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.s

server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o: src/managers/game_manager.cpp
server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o -MF CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o.d -o CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/game_manager.cpp

server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/game_manager.cpp > CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.i

server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/game_manager.cpp -o CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.s

server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o: src/managers/network_manager.cpp
server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o -MF CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o.d -o CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/network_manager.cpp

server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/network_manager.cpp > CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.i

server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/network_manager.cpp -o CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.s

server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o: src/managers/players_session_manager.cpp
server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o -MF CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o.d -o CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/players_session_manager.cpp

server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/players_session_manager.cpp > CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.i

server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/managers/players_session_manager.cpp -o CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.s

server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o: src/proto/r_type.pb.cc
server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o -MF CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o.d -o CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/proto/r_type.pb.cc

server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/proto/r_type.pb.cc > CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.i

server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/proto/r_type.pb.cc -o CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.s

server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o: src/systems/collision_systems.cpp
server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o -MF CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o.d -o CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/systems/collision_systems.cpp

server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/systems/collision_systems.cpp > CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.i

server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/systems/collision_systems.cpp -o CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.s

server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o: server/CMakeFiles/r-type_server.dir/flags.make
server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o: src/systems/velocity_system.cpp
server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o: server/CMakeFiles/r-type_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o -MF CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o.d -o CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o -c /home/tom/Epitech/RType/R-Type-Revival/server/src/systems/velocity_system.cpp

server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.i"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tom/Epitech/RType/R-Type-Revival/server/src/systems/velocity_system.cpp > CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.i

server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.s"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tom/Epitech/RType/R-Type-Revival/server/src/systems/velocity_system.cpp -o CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.s

# Object files for target r-type_server
r__type_server_OBJECTS = \
"CMakeFiles/r-type_server.dir/src/main.cpp.o" \
"CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o" \
"CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o" \
"CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o" \
"CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o" \
"CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o" \
"CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o" \
"CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o"

# External object files for target r-type_server
r__type_server_EXTERNAL_OBJECTS =

server/r-type_server: server/CMakeFiles/r-type_server.dir/src/main.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/managers/entity_manager.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/managers/game_manager.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/managers/network_manager.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/managers/players_session_manager.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/proto/r_type.pb.cc.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/systems/collision_systems.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/src/systems/velocity_system.cpp.o
server/r-type_server: server/CMakeFiles/r-type_server.dir/build.make
server/r-type_server: /usr/lib64/libboost_system.so.1.81.0
server/r-type_server: common/proto/libproto.a
server/r-type_server: /usr/lib64/libprotobuf.so
server/r-type_server: server/CMakeFiles/r-type_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tom/Epitech/RType/R-Type-Revival/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable r-type_server"
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/r-type_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/r-type_server.dir/build: server/r-type_server
.PHONY : server/CMakeFiles/r-type_server.dir/build

server/CMakeFiles/r-type_server.dir/clean:
	cd /home/tom/Epitech/RType/R-Type-Revival/server/server && $(CMAKE_COMMAND) -P CMakeFiles/r-type_server.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/r-type_server.dir/clean

server/CMakeFiles/r-type_server.dir/depend:
	cd /home/tom/Epitech/RType/R-Type-Revival/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/Epitech/RType/R-Type-Revival /home/tom/Epitech/RType/R-Type-Revival/server /home/tom/Epitech/RType/R-Type-Revival/server /home/tom/Epitech/RType/R-Type-Revival/server/server /home/tom/Epitech/RType/R-Type-Revival/server/server/CMakeFiles/r-type_server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : server/CMakeFiles/r-type_server.dir/depend

