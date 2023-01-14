cmake_minimum_required(VERSION 3.12)
project(CPP1_s21_matrixplus-0)

set(CMAKE_CPP_STANDARD 17)


set(SOURCES s21_matrix_oop.cpp s21_matrix_oop.h)

include_directories(.)

add_executable(C5 ${SOURCES})

target_link_libraries(C5 check -g)