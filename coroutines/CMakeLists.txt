cmake_minimum_required(VERSION 3.20)
project(corouties)

add_executable(simple_generator generator_app.cpp)
set_property(TARGET simple_generator PROPERTY CXX_STANDARD 23)

add_executable(coro_thread_sync thread_sync.cpp)
set_property(TARGET coro_thread_sync PROPERTY CXX_STANDARD 23)
