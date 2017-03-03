cmake_minimum_required(VERSION 3.6)
project(Cocurrent_Socket_Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        client/client.cpp
        server/starter_code2/example.c
        server/starter_code2/lex.yy.c
        server/starter_code2/parse.c
        server/starter_code2/parse.h
        server/starter_code2/y.tab.c
        server/starter_code2/y.tab.h
        server/example.c
        server/httpResponse.c
        server/httpResponse.h
        server/lex.yy.c
        server/parse.c
        server/parse.h
        server/server.c
        server/y.tab.c
        server/y.tab.h)

add_executable(Cocurrent_Socket_Server ${SOURCE_FILES})