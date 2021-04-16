cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

add_library(EmbeddedLogger STATIC
    logger.c
)

target_include_directories(EmbeddedLogger
    PRIVATE
        ../include/
    PUBLIC
        ../../include/
)
