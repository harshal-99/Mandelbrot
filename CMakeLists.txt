cmake_minimum_required(VERSION 3.17)
project(Mandelbrot)

set(CMAKE_CXX_STANDARD 20)

add_executable(Mandelbrot src/main.cpp src/Mandelbrot.cpp include/Mandelbrot.hpp)
add_executable(test test/main.cpp test/test.cpp)

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(Mandelbrot ${SFML_LIBRAIES} -lsfml-window -lsfml-system -lsfml-graphics -lpthread)
target_link_libraries(test ${SFML_LIBRAIES} -lsfml-window -lsfml-system -lsfml-graphics -lpthread)