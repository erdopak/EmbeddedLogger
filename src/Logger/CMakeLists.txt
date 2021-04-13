cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

add_library(EmbeddedLogger)

target_sources(EmbeddedLogger
    PRIVATE
       logger.c
    PUBLIC
        ${HEADER_LIST}    
)

target_include_directories(EmbeddedLogger
    PRIVATE
        ../include/
    PUBLIC
        ../../include/
)
