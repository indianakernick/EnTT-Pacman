cmake_minimum_required(VERSION 3.8)
project(EnTT_Example)

find_package(Curses REQUIRED)

add_executable(Game
        "src/main.cpp"
)

target_include_directories(Game
        PRIVATE
        ${CURSES_INCLUDE_DIRECTORIES}
)

target_link_libraries(Game
        PRIVATE
        ${CURSES_LIBRARIES}
)

target_compile_features(Game
        PRIVATE
        cxx_std_14
)

set_target_properties(Game
        PROPERTIES OUTPUT_NAME "example"
)