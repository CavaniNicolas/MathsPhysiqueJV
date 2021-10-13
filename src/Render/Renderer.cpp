
#include <iostream>

#include "Renderer.hpp"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char* function, const char* file, int line)
{
    // all existing errors are defined in <GL/glew.h>
    // translate error to hexadecimal to find it in <GL/glew.h>
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
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

void Renderer::draw(Shader& shader, Camera& camera, RenderedMesh& rendMesh) const
{
    // bind the shader
    shader.bind();
    // bind the vertex array (same as binding the buffer and seting up its layout)
    rendMesh.bind();

    // set the uniform values
    //    shader.setUniforms4f("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);
    shader.setUniforms1i("u_Texture", 0);

    const char* uniform = "u_MVP";
    // Exports the camera matrix to the Vertex Shader
    // mvp = proj * view * model !
    shader.setUniformsMat4f(uniform, camera.getProj() * camera.getView() * rendMesh.getModel());

    // Draw whats on the currently bound buffer
    GLCall(glDrawElements(
      GL_TRIANGLES, rendMesh.getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr)); // unsigned is important !
}
