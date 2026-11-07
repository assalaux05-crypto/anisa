
cmake_minimum_required(VERSION 3.16)
project(THEARDS C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(tiger_moth

    main.c 
    src/airship.c 
    src/engine.c 
    src/recruit.c 
    src/supplies.c 
    src/update_crew.c 
    src/wait_pirates.c 



)
target_include_directories(tiger_moth PRIVATE include)

target_compile_options(tiger_moth PRIVATE -Wall -Wextra -Werror -pedantic -pthread)
target_link_libraries(tiger_moth PRIVATE Threads::Threads)