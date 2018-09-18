cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

add_executable(Game
        "src/main.cpp"
        "src/curses.hpp"
        "src/graphics.cpp"
        "src/graphics.hpp"
        "src/game.cpp"
        "src/game.hpp"
        "src/sprites.cpp"
        "src/sprites.hpp"
        "src/color.hpp"
        "src/framebuf.hpp"
)

if(WIN32 OR MSVC)
        add_subdirectory(pdcurses)
        target_link_libraries(Game
                PRIVATE
                PDcurses
        )
        target_include_directories(Game
                PRIVATE
                include
        ) 
else()
        set(CURSES_NEED_NCURSES TRUE)
        find_package(Curses REQUIRED)

        target_include_directories(Game
                PRIVATE
                ${CURSES_INCLUDE_DIRECTORIES}
                ${CMAKE_SOURCE_DIR}/include
        )
        
        target_link_libraries(Game
                PRIVATE
                ${CURSES_LIBRARIES}
        )
endif()

target_compile_features(Game
        PRIVATE
        cxx_std_14
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