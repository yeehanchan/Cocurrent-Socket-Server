cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_STANDARD gcc)
link_directories(/usr/local/lib)
link_directories(starter_code2)
link_libraries(log4cplus)
set(SOURCE_FILES
        server.c parse.c y.tab.c lex.yy.c parser.y  httpResponse.c)
add_executable(server ${SOURCE_FILES})