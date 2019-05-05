cmake_minimum_required(VERSION 3.8)
project(entt-pacman)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
	include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup(TARGETS)
endif()

add_executable(entt-pacman
	src/main.cpp
	src/core/game.cpp
	src/core/game.hpp
	src/core/app.cpp
	src/core/app.hpp
	src/core/factories.cpp
	src/core/factories.hpp
	src/core/maze.cpp
	src/core/maze.hpp
	src/core/constants.hpp
	src/util/dir2vec.hpp
	src/util/registry.hpp
	src/comp/position.hpp
	src/comp/player.hpp
	src/comp/sprite.hpp
	src/comp/dir.hpp
	src/comp/home_position.hpp
	src/comp/ghost_mode.hpp
	src/comp/target.hpp
	src/comp/chase_target.hpp
	src/comp/ghost.hpp
	src/sys/movement.cpp
	src/sys/movement.hpp
	src/sys/player_input.cpp
	src/sys/player_input.hpp
	src/sys/render.cpp
	src/sys/render.hpp
	src/sys/eat_dots.cpp
	src/sys/eat_dots.hpp
	src/sys/can_move.cpp
	src/sys/can_move.hpp
	src/sys/pursue_target.cpp
	src/sys/pursue_target.hpp
	src/sys/set_target.cpp
	src/sys/set_target.hpp
	src/sys/player_ghost_collide.cpp
	src/sys/player_ghost_collide.hpp
	src/sys/change_ghost_mode.cpp
	src/sys/change_ghost_mode.hpp
	src/sys/house.cpp
	src/sys/house.hpp
)

target_include_directories(entt-pacman
	PRIVATE
		${CMAKE_SOURCE_DIR}/include
		${CMAKE_SOURCE_DIR}/src
)

target_compile_features(entt-pacman PRIVATE cxx_std_17)

# GLM 0.9.9.1 Suddenly produces a bunch of warnings
# They should sort it out in 0.9.9.2
target_compile_options(entt-pacman PRIVATE -Wall -Wextra -pedantic -Wno-gnu-anonymous-struct -Wno-nested-anon-types)

target_link_libraries(entt-pacman PRIVATE CONAN_PKG::sdl2)


add_custom_command(
	TARGET entt-pacman POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	        ${CMAKE_SOURCE_DIR}/assets/sheet
	        ${CMAKE_BINARY_DIR}
)