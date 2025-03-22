cmake_minimum_required(VERSION 3.29)
project(crime-sphere)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force using GCC compiler
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Add source files
add_executable(
        crime-sphere
        main.cpp
        FileProcessing.cpp
        Helpers.cpp
)

# Link against standard C++ library
target_link_libraries(crime-sphere stdc++)