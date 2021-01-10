cmake_minimum_required(VERSION 3.16)
project(GearShift)

set(CMAKE_CXX_STANDARD 20)
include_directories("${PROJECT_SOURCE_DIR}/SDL")
add_subdirectory(SDL)

add_executable(GearShift main.cpp include/SerialPort.h src/SerialPort.cpp src/Logger.cpp include/Logger.h)
target_link_libraries(GearShift SDL2)