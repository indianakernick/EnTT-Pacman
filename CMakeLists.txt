cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

add_executable(Game
        "src/main.cpp"
        "src/core/game.cpp"
        "src/core/game.hpp"
        "src/core/app.cpp"
        "src/core/app.hpp"
        "src/core/factories.cpp"
        "src/core/factories.hpp"
        "src/core/maze.cpp"
        "src/core/maze.hpp"
        "src/core/dimensions.hpp"
        "src/util/dir2vec.hpp"
        "src/util/registry.hpp"
        "src/comp/position.hpp"
        "src/comp/player.hpp"
        "src/comp/sprite.hpp"
        "src/comp/dir.hpp"
        "src/comp/home_position.hpp"
        "src/comp/ghost_mode.hpp"
        "src/comp/target.hpp"
        "src/comp/chase_target.hpp"
        "src/comp/ghost.hpp"
        "src/sys/movement.cpp"
        "src/sys/movement.hpp"
        "src/sys/player_input.cpp"
        "src/sys/player_input.hpp"
        "src/sys/render.cpp"
        "src/sys/render.hpp"
        "src/sys/eat_dots.cpp"
        "src/sys/eat_dots.hpp"
        "src/sys/can_move.cpp"
        "src/sys/can_move.hpp"
        "src/sys/pursue_target.cpp"
        "src/sys/pursue_target.hpp"
        "src/sys/set_chase_target.cpp"
        "src/sys/set_chase_target.hpp"
        "src/sys/set_scared_target.cpp"
        "src/sys/set_scared_target.hpp"
        "src/sys/set_scatter_target.cpp"
        "src/sys/set_scatter_target.hpp"
        "src/sys/player_lose.cpp"
        "src/sys/player_lose.hpp"
        "src/sys/change_ghost_mode.cpp"
        "src/sys/change_ghost_mode.hpp"
)

if(CMAKE_TOOLCHAIN_FILE)
        find_package(SDL2 CONFIG REQUIRED)
        target_link_libraries(Game 
                PRIVATE 
                SDL2::SDL2 
                SDL2::SDL2main
        )
else()
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
        find_package(SDL2 REQUIRED)

        target_include_directories(Game
                PRIVATE
                "${SDL2_INCLUDE_DIR}"
        )
        target_link_libraries(Game
                PRIVATE
                "${SDL2_LIBRARY}"
        )
endif()

target_include_directories(Game
        PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/src"
)

target_compile_features(Game
        PRIVATE
        cxx_std_17
)

if (CMAKE_BUILD_TYPE MATCHES DEBUG)
        target_compile_options(Game
                PRIVATE
                -Wall -Wextra -pedantic
                # GLM 0.9.9.1 Suddenly produces a bunch of warnings
                # They should sort it out in 0.9.9.2
                -Wno-gnu-anonymous-struct -Wno-nested-anon-types
        )
endif()

set_target_properties(Game
        PROPERTIES OUTPUT_NAME "example"
)

add_custom_command(
	    TARGET Game POST_BUILD
	    COMMAND ${CMAKE_COMMAND} -E copy_directory
	            ${CMAKE_SOURCE_DIR}/assets/sheet
	            ${CMAKE_BINARY_DIR}
)