cmake_minimum_required(VERSION 3.20)
project(ui_examples)

find_package(OpenGL REQUIRED)

create_executable(
    TARGET ui_example_1
    SOURCES main.cpp
    LIBS glfw ImGui glad ${OPENGL_LIBRARIES}
)

create_executable(
    TARGET glfw_coro
    SOURCES glfw_coro.cpp
    LIBS glfw glad ${OPENGL_LIBRARIES}
)
