cmake_minimum_required(VERSION 3.20)
project(ui_examples)

add_executable(ui_example_1 main.cpp)
target_link_libraries(ui_example_1 PRIVATE glfw ImGui glad
					  ${OPENG_LIBRARIES})
set_property(TARGET ui_example_1 PROPERTY CXX_STANDARD 23)
