cmake_minimum_required(VERSION 3.14)
project(fractal C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-o3 -lmlx -framework OpenGL -framework AppKit")
set(CMAKE_C_FRA)

include_directories(inc)
include_directories(libft)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(fractal
        inc/fractol.h
        src/main.c
        src/loop.c
        src/calculation.c src/formulas.c src/draw.c src/zoom.c src/initialize.c src/cl_init.c)

target_link_libraries(fractal /Users/smight/Desktop/fractal/libft/libft.a)
target_link_libraries(fractal "libmlx.a")
target_link_libraries(fractal "-framework AppKit")
target_link_libraries(fractal "-framework OpenGL")