cmake_minimum_required(VERSION 3.0.2)
project(dynamixel_workbench)

add_compile_options(-std=c++14)

include_directories(
        ../src
)

add_library(dynamixel_workbench
        lib/dw/src/dynamixel_workbench_toolbox/dynamixel_item.cpp
        lib/dw/src/dynamixel_workbench_toolbox/dynamixel_driver.cpp
        lib/dw/src/dynamixel_workbench_toolbox/dynamixel_tool.cpp
        lib/dw/src/dynamixel_workbench_toolbox/dynamixel_workbench.cpp
        DynamixelWorkbench.h)

target_link_libraries(dynamixel_workbench LINK_PUBLIC "/usr/local/lib/libdxl_x64_cpp.so")


add_executable(Manipulator Manipulator.ino Servo.cpp Servo.h)
target_link_libraries(Manipulator LINK_PUBLIC dynamixel_workbench)