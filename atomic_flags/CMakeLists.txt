cmake_minimum_required(VERSION 3.20)
project(atomic_sync)

add_executable(atomic_sync atomic_sync.cpp)
set_property(TARGET atomic_sync PROPERTY CXX_STANDARD 23)
