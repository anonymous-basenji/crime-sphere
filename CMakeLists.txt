cmake_minimum_required(VERSION 3.29)
project(crime-sphere)

set(CMAKE_CXX_STANDARD 11)

add_executable(crime-sphere main.cpp FileProcessing.cpp Helpers.cpp)
