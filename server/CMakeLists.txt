cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        server.cpp)
link_directories(/usr/local/lib)
link_libraries(log4cplus)
add_executable(server ${SOURCE_FILES})