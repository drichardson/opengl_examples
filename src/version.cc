#include "common.h"

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


