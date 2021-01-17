cmake_minimum_required(VERSION 3.17)
project(source)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(source main.cpp peripherals/Aes.cpp peripherals/Aes.h peripherals/TimerRegister.cpp peripherals/TimerRegister.h peripherals/Futurama.cpp peripherals/Futurama.h kernel/Processes.h threads/SyncPoint.h)