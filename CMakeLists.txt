cmake_minimum_required(VERSION 3.13)
project(pipex)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -g -foptimize-sibling-calls -O2") #
add_subdirectory(ft_printf)
set(SOURCE_FILES
        src/main.c
        src/fdc.c
        src/path.c)
set(BONUS_SRC
        src/main_bonus.c
        src/fdc.c
        src/path.c
        src/fps_bonus.c
        src/fps2_bonus.c)
add_executable(pipex ${SOURCE_FILES})
target_link_libraries(pipex ft_printf)
add_executable(pipex_bonus ${BONUS_SRC})
target_link_libraries(pipex_bonus ft_printf)