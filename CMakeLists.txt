cmake_minimum_required(VERSION 3.20)
project(led_control_esp32)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(led_control_esp32
        include/Button.h
        include/LedStripeModi.h
        include/mqttData.h
        src/Button.cpp
        src/LedStripeModi.cpp
        src/main.cpp
        test/testbutton.cpp)
