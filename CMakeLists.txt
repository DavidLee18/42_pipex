cmake_minimum_required(VERSION 3.13)
project(pipex)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -g")
add_subdirectory(ft_printf)
set(SOURCE_FILES
        src/main.c
        src/fdc.c
        src/path.c)
set(BONUS_SRC )
add_executable(pipex ${SOURCE_FILES})
target_link_libraries(pipex ft_printf)