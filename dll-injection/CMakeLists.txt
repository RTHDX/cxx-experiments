cmake_minimum_required(VERSION 3.20)
project(dll-injection)

add_library(dll_library SHARED dll.hpp dll.cpp)

add_executable(application application.cpp)
target_link_libraries(application PUBLIC dll_library)
