cmake_minimum_required(VERSION 3.6)
project(LAB2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp)

add_executable(LAB2 ${SOURCE_FILES})

find_package(Threads REQUIRED)
target_link_libraries(LAB2 Threads::Threads)
