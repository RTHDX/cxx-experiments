cmake_minimum_required(VERSION 3.20)
project(cxx-examples)

function (create_executable)
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak")
    endif ()
    cmake_parse_arguments(THIS "" "TARGET" "SOURCES" ${ARGV})
    add_executable(${THIS_TARGET} ${THIS_SOURCES})
    set_property(TARGET ${THIS_TARGET} PROPERTY CXX_STANDARD 23)
endfunction ()

add_subdirectory(3rdParty/glad)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glad/include")

add_subdirectory(3rdParty/glfw)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glfw")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glfw/include")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/backends")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/glm")

add_library(ImGui STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/imgui_widgets.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/backends/imgui_impl_opengl3.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/imgui.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/backends/imgui_impl_glfw.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/imgui/backends/imgui_impl_opengl3.h"
)

add_subdirectory(dll-injection)
add_subdirectory(atomic_flags)
add_subdirectory(coroutines)
add_subdirectory(ui)
add_subdirectory(iterators)
add_subdirectory(classes)
add_subdirectory(ranges)
add_subdirectory(glm_experiments)
