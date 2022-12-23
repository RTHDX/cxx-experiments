cmake_minimum_required(VERSION 3.20)
project(iterators)

add_executable(forward_iterators forward_iterator.cpp)
set_property(TARGET forward_iterators PROPERTY CXX_STANDARD 23)
