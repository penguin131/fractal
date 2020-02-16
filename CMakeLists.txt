cmake_minimum_required(VERSION 3.14)
project(fractol C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-O3 -lmlx -framework OpenGL -framework AppKit")
set(CMAKE_C_FRA)

include_directories(inc)
include_directories(libft)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(fractol
        inc/fractol.h
        src/main.c
        src/loop.c
        src/calculation.c src/formulas.c src/draw.c src/zoom.c src/initialize.c)

target_link_libraries(fractol /Users/bootcamp/Desktop/C/fractol/libft/libft.a)
target_link_libraries(fractol "libmlx.a")
target_link_libraries(fractol "-framework AppKit")
target_link_libraries(fractol "-framework OpenGL")
