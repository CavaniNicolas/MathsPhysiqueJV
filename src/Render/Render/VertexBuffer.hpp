#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace render
{

// Structure to standardize the vertices used in the meshes
struct Vertex
{
    glm::vec3 position;
    //    glm::vec3 color;
    glm::vec2 texture;
};

class VertexBuffer
{
  private:
    // index buffer object has to be unsigned ! (but can be char or short for
    // memory savings
    unsigned int m_bufferID;

  public:
    VertexBuffer(const void* data, unsigned int size);
    VertexBuffer(const std::vector<Vertex>& vertices);

    // We dont want to be able to copy as we simply handle it using an int
    // for the moment, and not a memory address to the actual opengl object
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

} // namespace render
