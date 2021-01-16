cmake_minimum_required(VERSION 3.17)
project(source)

set(CMAKE_CXX_STANDARD 14)

add_executable(source main.cpp Aes.cpp Aes.h TimerRegister.cpp TimerRegister.h)