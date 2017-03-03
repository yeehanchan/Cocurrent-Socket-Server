cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_STANDARD gcc)

set(SOURCE_FILES client.c)

add_executable(client ${SOURCE_FILES})