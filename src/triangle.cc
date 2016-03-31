#include "window.h"
#include "shaders.h"

const char* vertex_shader_source = "";
const char* fragment_shader_source = "";

int main()
{
    common::Window* window = common::Window::CreateWindow();
    window->LoadOpenGLCoreProfile();
    window->MakeContextCurrent();

    glViewport(0, 0, window->getWidth(), window->getHeight());

    //shaders::LoadShaderFromString(GL_FRAGMENT_SHADER, fragment_shader_source, &fragment_shader);

    auto render = []() {
        constexpr GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, white);
    };

    window->RunLoop(render);

    return 0;
}

