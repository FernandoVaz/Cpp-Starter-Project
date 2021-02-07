cmake_minimum_required(VERSION 3.16)
project(GearShift)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(GearShift
        include/Logger.h
        include/SerialPort.h
        src/main/Logger.cpp
        src/main/SerialPort.cpp
        CMakeLists.txt
        main.cpp)
