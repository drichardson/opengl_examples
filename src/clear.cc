#include "common.h"

int main()
{
    common::Window* window = common::Window::CreateWindow();
    window->LoadOpenGLCoreProfile();
    window->MakeContextCurrent();

    glViewport(0, 0, window->getWidth(), window->getHeight());

    auto render = []() {
        constexpr GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, white);
    };

    window->RunLoop(render);

    return 0;
}

