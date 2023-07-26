#include <GLFW/glfw3.h>
#include <coroutine>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>


using namespace std::chrono_literals;
using default_handler_t = std::coroutine_handle<>;

struct glfw_handler_t final {
    std::shared_ptr<default_handler_t> handle;

    void operator () (GLFWwindow*, int key, int, int action, int) {
        if (action == GLFW_PRESS) {
            default_handler_t::from_address(handle->address()).resume();
        }
    }
};

struct wait_for_key_awaiter_t {
    GLFWwindow* window;
    int key;

    bool await_ready() { return glfwGetKey(window, key) == GLFW_PRESS; }

    void await_suspend(default_handler_t handle) {
        glfw_handler_t glfw_h {.handle = std::make_shared<std::coroutine_handle<>>(handle)};
        glfwSetKeyCallback(window, (GLFWkeyfun)(&glfw_h));
    }

    void await_resume() {}
};

struct wait_for_key_t {
    GLFWwindow* window;
    int key;

    wait_for_key_awaiter_t operator co_await() { return { window, key }; }
};

wait_for_key_awaiter_t wait_for_key(GLFWwindow* window, int key) {
    return { .window = window, .key = key };
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // Wait for user to press 'Q' key
        auto coroutine = wait_for_key(window, GLFW_KEY_Q);
        while (!coroutine.await_ready()) {
            glfwPollEvents();
            std::this_thread::sleep_for(50ms);
        }
        coroutine.await_resume();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
