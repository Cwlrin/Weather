cmake_minimum_required(VERSION 3.17)
project(Weather)

set(CMAKE_CXX_STANDARD 14)

add_executable(Weather cJSON.c cJSON.h main.cpp utf8togbk.c utf8togbk.h)

target_link_libraries(Weather C:/MinGW/lib/libwsock32.a)