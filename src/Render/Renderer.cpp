
#include <iostream>
#include "Renderer.hpp"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    // all existing errors are defined in <GL/glew.h>
    // translate error to hexadecimal to find it in <GL/glew.h>
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::clear() const
{
    GLCall(glClear( GL_COLOR_BUFFER_BIT ));
}

void Renderer::draw(VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    // bind the shader
    shader.bind();
    // bind the vertex array (same as binding the buffer and seting up its layout)
    va.bind();
    // bind the index buffer
    ib.bind();

    // Draw whats on the currently bound buffer
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr)); // unsigned is important !
}
