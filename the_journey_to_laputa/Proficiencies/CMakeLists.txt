cmake_minimum_required(VERSION 3.16)
project(journey_proficiencies C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(FUNDA "${CMAKE_CURRENT_SOURCE_DIR}/../Fundamentals")

add_executable(game
   game/main.c
    game/game.c
    game_state/game_state.c
    game_logic/cannon.c
    game_logic/enemy.c
    user_logic/player.c
    ${FUNDA}/src/airship.c
    ${FUNDA}/src/engine.c
    ${FUNDA}/src/update_crew.c
    display/display.o
    display/terminal.o
    user_logic/input.o
    game_logic/actions.o
)

target_include_directories(game PRIVATE
    display
    game
    game_logic
    game_state
    user_logic
    ${FUNDA}/include
)

target_compile_options(game PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
)

target_link_libraries(game PRIVATE
    Threads::Threads
)