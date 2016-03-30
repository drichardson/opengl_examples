#ifndef OPENGL_EXAMPLES_COMMON_H
#define OPENGL_EXAMPLES_COMMON_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

namespace common {

namespace {

void ErrorCallback(int error, const char* description) {
    std::cerr << "glfw error: " << description << std::endl;
}

};

class Window {
    int width_ = 0;
    int height_ = 0;
    GLFWwindow* window_ = nullptr;

    Window(GLFWwindow* window, int width, int height)
        : window_(window),
        width_(width),
        height_(height)
    {
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

public:

    inline int getWidth() const { return width_; }
    inline int getHeight() const { return height_; }

    static Window* CreateWindow(int width=640, int height=480, char const* title = "OpenGL Example")
    {
        if (!glfwInit()) {
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

    void MakeContextCurrent()
    {
        glfwMakeContextCurrent(window_);
    }

    bool LoadOpenGLCoreProfile()
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

    bool RunLoop(std::function<void(void)> render)
    {
        /* Loop until the user closes the window */
        GLFWwindow* window = static_cast<GLFWwindow*>(window_);
        while (!glfwWindowShouldClose(window)) {

            render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return true;
    }
};

}

#endif

