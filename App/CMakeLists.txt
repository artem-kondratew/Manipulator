cmake_minimum_required(VERSION 3.18)
project(Manipulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Manipulator main.cpp ../Arduino/Config.h graphics.h Connect.h Connect.cpp str.h str.cpp Gservo.h Gservo.cpp History.h List.h Exception.h)

target_link_libraries(${PROJECT_NAME} ncurses)