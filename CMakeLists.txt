cmake_minimum_required(VERSION 3.21)
project(untitled11 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled11 main.c Estruturas.c Funcoes.c Ficheiros.c Ficheiros.h)
add_compile_options(-Wall -Wextra)