cmake_minimum_required(VERSION 2.8)

project(sorting)

set(SOURCE sorting.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -O0 -ggdb3")

add_library(sorting STATIC ${SOURCE})