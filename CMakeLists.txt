cmake_minimum_required(VERSION 4.3)
project(ProjetoFragatas C)

set(CMAKE_C_STANDARD 11)

add_executable(ProjetoFragatas main.c
        fragata.c
        fragata.h)
