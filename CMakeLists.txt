cmake_minimum_required(VERSION 3.4.1)

project(OPENGL_EXAMPLES
    LANGUAGES CXX C
    VERSION 0.1.0.0
    )

# Build GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")
add_subdirectory(glfw)

set(CMAKE_CXX_STANDARD 14)

include_directories(
    glfw/include
    gl3w/include
    .
    )

# Stack protection
add_compile_options(-fstack-protector-strong)

add_library(gl3w
    gl3w/gl3w.c
    )

link_libraries(
    glfw
    ${GLFW_LIBRARIES}
    gl3w
    )

add_executable(version src/version.cc)
add_executable(clear src/clear.cc)


