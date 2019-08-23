cmake_minimum_required(VERSION 3.14)
project(clearning C)
file(GLOB SOURCES
        lib/common.h
        socket/socket_tcp.h
        socket/*
        //*号对应具体的文件名
        *.c
        )
set(CMAKE_C_STANDARD 99)

add_executable(clearning main.c ${SOURCE_FILES} ${SOURCES})

