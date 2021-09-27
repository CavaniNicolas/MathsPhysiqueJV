
#pragma once

#include <GL/glew.h>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

// MSVC macro to break the program
#define ASSERT(x) if (!(x)) __debugbreak();

// macro to wrap opengl functions to assert errors without having to wrap the functions ourselves
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void clear() const;
    void draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
