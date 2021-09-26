
#pragma once

#include <GL/glew.h>

// MSVC macro to break the program
#define ASSERT(x) if (!(x)) __debugbreak();

// macro to wrap opengl functions to assert errors without having to wrap the functions ourselves
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
