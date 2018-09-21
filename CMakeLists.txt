cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

set(ENV{TERM} "xterm-256color")

add_executable(Game
        "src/main.cpp"
        "src/curses.hpp"
        "src/registry.hpp"
        "src/graphics.cpp"
        "src/graphics.hpp"
        "src/game.cpp"
        "src/game.hpp"
        "src/sprites.cpp"
        "src/sprites.hpp"
        "src/factories.cpp"
        "src/factories.hpp"
        "src/color.hpp"
        "src/framebuf.cpp"
        "src/framebuf.hpp"
        "src/dir to vec.hpp"
        "src/sprite component.hpp"
        "src/position component.hpp"
        "src/player component.hpp"
        "src/desired dir component.hpp"
        "src/random dir component.hpp"
        "src/blit sprites system.cpp"
        "src/blit sprites system.hpp"
        "src/movement system.cpp"
        "src/movement system.hpp"
        "src/get camera system.cpp"
        "src/get camera system.hpp"
        "src/player input system.cpp"
        "src/player input system.hpp"
        "src/clear desired dir system.cpp"
        "src/clear desired dir system.hpp"
        "src/random movement system.cpp"
        "src/random movement system.hpp"
        "src/limit movement system.cpp"
        "src/limit movement system.hpp"
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

if (DISABLE_MAINLOOP)
        target_compile_definitions(Game
                PRIVATE
                -DDISABLE_MAINLOOP
        )
endif()

set_target_properties(Game
        PROPERTIES OUTPUT_NAME "example"
)