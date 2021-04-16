cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
find_package(GTest REQUIRED)

enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(EmbeddedLogger_Test
    main_test.cpp
)

target_link_libraries(EmbeddedLogger_Test
        ${GTEST_LIBRARIES} 
        ${GTEST_MAIN_LIBRARIES}    
        pthread
        EmbeddedLogger
)
