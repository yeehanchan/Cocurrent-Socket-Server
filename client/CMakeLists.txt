cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES client.cpp)

link_directories(/usr/local/lib)
link_libraries(log4cplus)
add_executable(client ${SOURCE_FILES})