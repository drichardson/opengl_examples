#include "shaders.h"

namespace {

//
// Create a shader object, load the shader source, and
// compile the shader.
//
bool LoadShaderFromString(GLenum type, const char *shader_source, GLuint* shader_out)
{
    GLuint shader;
    GLint compiled;

    // Create the shader object
    shader = glCreateShader(type);

    if (shader == 0)
        return false;

    // Load the shader source
    glShaderSource (shader, 1, &shader_source, NULL);

    // Compile the shader
    glCompileShader(shader);

    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) 
    {
        GLint infoLen = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

        if (infoLen > 1)
        {
            char* infoLog = new char[infoLen];
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            std::cerr << "Error compiling shader:\n" << infoLog << std::endl;
            delete[] infoLog;
        }

        glDeleteShader(shader);
        return false;
    }

    if (shader_out) {
        *shader_out = shader;
    } else {
        glDeleteShader(shader);
    }

    return true;
}

bool AttachShader(GLuint program, GLenum shader_type, char const* shader_source)
{
    GLuint shader;
    bool ok = LoadShaderFromString(shader_type, shader_source, &shader);
    if (!ok) {
        std::cerr << "Failed to attach shader type " << shader_type << "\n";
        return false;
    }

    glAttachShader(program, shader);
    glDeleteShader(shader); // won't be deleted until program is delted.
    return true;
}

}

namespace common {

bool LinkProgram(GLuint program, char const* vertex_shader_path, char const* fragment_shader_path)
{
    bool ok = AttachShader(program, GL_VERTEX_SHADER, vertex_shader_path);
    if (!ok)
    {
        std::cerr << "Failed to attach vertex shader " << vertex_shader_path << "\n";
        return false;
    }

    ok = AttachShader(program, GL_FRAGMENT_SHADER, fragment_shader_path);
    if (!ok)
    {
        std::cerr << "Failed to attach fragment shader " << fragment_shader_path << "\n";
        return false;
    }

    glLinkProgram(program);

    GLint link_status;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == 0)
    {
        GLint info_len = 0;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_len);

        if (info_len > 1)
        {
            char* info_log = new char[info_len];
            glGetProgramInfoLog(program, info_len, NULL, info_log);
            std::cerr << "Error linking program: " << info_log << std::endl;
            delete[] info_log;
        }

        return false;
    }

    return true;
}

}

