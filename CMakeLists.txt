cmake_minimum_required(VERSION 3.10)

project(yabasugibot)

set(CMAKE_CXX_STANDARD 20)

find_package(dpp REQUIRED)

add_executable(yabasugibot main.cpp)

target_link_libraries(yabasugibot dpp::dpp)