cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(Logger_Test
    loggerTests.cpp
)

target_link_libraries(Logger_Test
        ${GTEST_LIBRARIES} 
        ${GTEST_MAIN_LIBRARIES}    
        pthread
        EmbeddedLogger
)
