#ifndef OPENGL_EXAMPLES_SHADERS_H
#define OPENGL_EXAMPLES_SHADERS_H

#include <GL/gl3w.h>

#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace common {

// Create vertex and fragment shader objects, load the source, compile them, and link them into the given program.
bool LinkProgram(GLuint program, char const* vertex_shader_source, char const* fragment_shader_source);

}

#endif

