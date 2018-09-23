cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

add_executable(Game
        "src/main.cpp"
        "src/registry.hpp"
        "src/game.cpp"
        "src/game.hpp"
        "src/application.cpp"
        "src/application.hpp"
        "src/factories.cpp"
        "src/factories.hpp"
        "src/dir to vec.hpp"
        "src/dimensions.hpp"
        "src/maze.cpp"
        "src/maze.hpp"
        "src/position component.hpp"
        "src/player component.hpp"
        "src/player sprite component.hpp"
        "src/desired dir component.hpp"
        "src/actual dir component.hpp"
        "src/maze sprite component.hpp"
        "src/target component.hpp"
        "src/blinky target component.hpp"
        "src/pinky target component.hpp"
        "src/inky target component.hpp"
        "src/clyde target component.hpp"
        "src/movement system.cpp"
        "src/movement system.hpp"
        "src/player input system.cpp"
        "src/player input system.hpp"
        "src/clear desired dir system.cpp"
        "src/clear desired dir system.hpp"
        "src/maze render system.cpp"
        "src/maze render system.hpp"
        "src/player render system.cpp"
        "src/player render system.hpp"
        "src/wall collide system.cpp"
        "src/wall collide system.hpp"
        "src/dot render system.cpp"
        "src/dot render system.hpp"
        "src/eat dots system.cpp"
        "src/eat dots system.hpp"
        "src/ghost render system.cpp"
        "src/ghost render system.hpp"
        "src/target system.cpp"
        "src/target system.hpp"
        "src/blinky target system.cpp"
        "src/blinky target system.hpp"
        "src/pinky target system.cpp"
        "src/pinky target system.hpp"
        "src/inky target system.cpp"
        "src/inky target system.hpp"
        "src/clyde target system.cpp"
        "src/clyde target system.hpp"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(SDL2 REQUIRED)

target_include_directories(Game
        PRIVATE
        "${SDL2_INCLUDE_DIR}"
        "${CMAKE_SOURCE_DIR}/include"
)
       
target_link_libraries(Game
        PRIVATE
        "${SDL2_LIBRARY}"
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