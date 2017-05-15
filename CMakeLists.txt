cmake_minimum_required(VERSION 3.6)
project(FRACTOL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lmlx -framework OpenGL -framework AppKit")
set(SOURCE_FILES
    main.c colour.c FRACTOL.h)

add_executable(FRACTOL ${SOURCE_FILES})
target_link_libraries(FRACTOL ${CMAKE_SOURCE_DIR}/libft/libft.a)