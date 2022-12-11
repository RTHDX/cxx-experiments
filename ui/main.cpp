#include <thread>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


void main_imgui_window(const char* title) {
    ImGui::Begin(title);
    if (ImGui::Button("Button")) {
        std::cout << "Button pressed" << std::endl;
    }
    ImGui::End();
}


int main() {
    if (!glfwInit()) {
        return 1;
    }

    const char* glsl_version = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    glfwWindowHint(GLFW_SAMPLES, 4);

    auto* window = glfwCreateWindow(800, 600, "test 1", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return 1;
    }
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        main_imgui_window("main window");

        ImGui::Render();
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
