#include "shaders.h"
#include "window.h"
#include <GL/gl3w.h>
#include <cstdlib>
#include <iostream>

const char* vertex_shader_source =
"#version 410 core \n"
"void main() \n"
"{ \n"
"   gl_Position = vec4(0, 0, 0, 1.0); \n"
"}\n";

const char* fragment_shader_source =
"#version 410 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"   color = vec4(1, 0, 0, 1);\n"
"}\n";

int main()
{
    common::Window* window = common::Window::CreateWindow();
    window->LoadOpenGLCoreProfile();
    window->MakeContextCurrent();

    glViewport(0, 0, window->getWidth(), window->getHeight());

    GLuint program = glCreateProgram();
    bool ok = common::LinkProgram(program, vertex_shader_source, fragment_shader_source);
    if (!ok)
    {
        std::cerr << "Error linking shaders.\n";
        std::exit(1);
    }

    // The values in the vertex array are ignored by the vertex shader, but is required to get it to render a point.
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    auto render = [program]() {
        constexpr GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

        glClearBufferfv(GL_COLOR, 0, white);

        glUseProgram(program);
        glPointSize(40.0f);
        glDrawArrays(GL_POINTS, 0, 1);
    };

    window->RunLoop(render);

    glDeleteVertexArrays(1, &vao);

    return 0;
}

