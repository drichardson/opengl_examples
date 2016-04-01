#include "shaders.h"
#include "window.h"
#include <GL/gl3w.h>
#include <cstdlib>
#include <iostream>

const char* vertex_shader_source =
"#version 410 core\n"
"layout(location=0) in vec4 position;\n"
"void main()\n"
"{\n"
"   gl_Position = position;\n"
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

    GLint max_attributes = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attributes);
    std::cout << "Max attributes is " << max_attributes << "\n";

    // The vertex array object stores all the state
    // https://www.opengl.org/wiki/Vertex_Specification#Vertex_Array_Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    std::cout << "vao is " << vao << "\n";
    glBindVertexArray(vao);

    GLfloat triangle_verticies[] = {
        -1, -1, 0,
        0, 1, 0,
        1, -1, 0,
    };

    // Generate a name for a buffer object. We will copy the triangle_verticies above into the buffer
    // object so it can be accessed by the GPU.
    // https://www.opengl.org/wiki/Buffer_Object
    // https://www.opengl.org/wiki/Vertex_Specification#Vertex_Buffer_Object
    GLuint vbo;
    // Generate a buffer object name (i.e., handle to the buffer)
    glGenBuffers(1, &vbo); 
    // Bind the buffer to the array buffer of the current context. Pre OpenGL 4.5, you have to bind objects
    // to the current context in order to modify them. In OpenGL 4.5, you can alternatively use
    // Direct State Access (https://www.opengl.org/wiki/Direct_State_Access) to modify the objects without
    // having to bind them to the current context.
    // Note: glBindBuffer does not effect the VAOs state, it only effects the global OpenGL state. However,
    // binding is required to supply buffer data via glBufferData and also to associate the buffer with
    // an attribute location (i.e., the location that matches the vertex shader's input attribute location).
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    // Copy the triangle_verticies into the bound buffer object (vbo).
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_verticies), triangle_verticies, GL_STATIC_DRAW);

    // Describe the format of the array bound to the global OpenGL state GL_ARRAY_BUFFER.
    constexpr int position_attribute_location = 0; // must match location of position attribute in vertex shader
    glVertexAttribPointer(position_attribute_location, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Vertex attributes are numbered from 0 to GL_MAX_VERTEX_ATTRIBS - 1. Each attribute can be enabled or disabled for array access.
    // When an attribute's array access is disabled, any reads of that attribute by the vertex shader will produce a
    // constant value instead of a value pulled from an array.
    glEnableVertexAttribArray(position_attribute_location);

    // Unbind the VAO (just to mimic a more realistic application with several VAOs)..
    glBindVertexArray(0);


    auto render = [program, vao]() {
        constexpr GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

        glClearBufferfv(GL_COLOR, 0, white);

        glUseProgram(program);

        // Bind the VAO previously defined. This uses the state of the VAO we defined before the render
        // loop. That is, it binds the VBO initialized with the triangle_verticies data at location 0.
        glBindVertexArray(vao);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    };

    window->RunLoop(render);

    // Cleanup OpenGL objects.
    glDeleteProgram(program);
    glDisableVertexAttribArray(1);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return 0;
}

