#ifndef OPENGL_EXAMPLES_COMMON_H
#define OPENGL_EXAMPLES_COMMON_H

#include <functional>

class GLFWwindow;

namespace common {

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

    static Window* CreateWindow(int width=640, int height=480, char const* title = "OpenGL Example");

    void MakeContextCurrent();
    bool LoadOpenGLCoreProfile();
    void RunLoop(std::function<void(void)> render);
};

}

#endif

