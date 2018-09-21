cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

add_executable(Game
        "src/main.cpp"
        "src/registry.hpp"
        "src/game.cpp"
        "src/game.hpp"
        "src/factories.cpp"
        "src/factories.hpp"
        "src/dir to vec.hpp"
        "src/sprite component.hpp"
        "src/position component.hpp"
        "src/player component.hpp"
        "src/desired dir component.hpp"
        "src/blit sprites system.cpp"
        "src/blit sprites system.hpp"
        "src/movement system.cpp"
        "src/movement system.hpp"
        "src/player input system.cpp"
        "src/player input system.hpp"
        "src/clear desired dir system.cpp"
        "src/clear desired dir system.hpp"
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

message(STATUS "${SDL2_LIBRARY}")

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