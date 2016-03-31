#include "window.h"
#include <GL/gl3w.h>
#include <iostream>

int main()
{
    common::Window* window = common::Window::CreateWindow();
    window->LoadOpenGLCoreProfile();
    window->MakeContextCurrent();

    std::cout <<
        "OpenGL Version: " << glGetString(GL_VERSION) << "\n" <<
        "OpenGL Vendor: " << glGetString(GL_VENDOR) << "\n";

    return 0;
}


