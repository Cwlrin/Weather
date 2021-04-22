cmake_minimum_required(VERSION 3.17)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c cJSON.c cJSON.h utf8togbk.c utf8togbk.h)