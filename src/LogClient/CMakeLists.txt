cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

add_library(LogClient STATIC
    logClient.c
)

target_include_directories(LogClient
    PUBLIC
        ../../include/
        ./
)