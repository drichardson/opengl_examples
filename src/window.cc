#include "window.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

namespace common {

namespace {

void ErrorCallback(int error, const char* description) {
    std::cerr << "glfw error: " << description << std::endl;
}

}

Window* Window::CreateWindow(int width, int height, char const* title)
{
    if (!glfwInit())
    {
        return nullptr;
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == nullptr) {
        glfwTerminate();
        return nullptr;
    }

    return new Window(window, width, height);
}

void Window::MakeContextCurrent()
{
    glfwMakeContextCurrent(window_);
}

bool Window::LoadOpenGLCoreProfile()
{
    MakeContextCurrent();

    // Use gl3w to load the OpenGL Core Profile after the window's OpenGL context is made current.
    int rc = gl3wInit();

    if (rc != 0) {
        std::cerr << "gl3wInit failed to load OpenGL Core Profile with " << rc << std::endl;
        return false;
    }

    return true;
}

void Window::RunLoop(std::function<void(void)> render)
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window_)) {

        render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window_);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

}


