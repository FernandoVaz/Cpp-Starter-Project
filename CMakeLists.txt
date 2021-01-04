cmake_minimum_required(VERSION 3.16)
project(GearShift)

set(CMAKE_CXX_STANDARD 20)

add_executable(GearShift main.cpp include/SerialPort.h src/SerialPort.cpp src/Logger.cpp include/Logger.h)