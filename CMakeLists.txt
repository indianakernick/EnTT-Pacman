cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

add_executable(Game
        "src/main.cpp"
        "src/curses.hpp"
)

if(WIN32 OR MSVC)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
        find_package(PDCurses REQUIRED)
        set(CURSES_INCLUDE_DIRECTORIES PDCURSES_INCLUDE_DIR)
        set(CURSES_LIBRARIES PDCURSES_LIBRARIES)
else()
        set(CURSES_NEED_NCURSES TRUE)
        find_package(Curses REQUIRED)
endif()

target_include_directories(Game
        PRIVATE
        ${CURSES_INCLUDE_DIRECTORIES}
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Game
        PRIVATE
        ${CURSES_LIBRARIES}
)

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