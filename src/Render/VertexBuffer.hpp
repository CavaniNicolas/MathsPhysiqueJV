#pragma once

#include <glm/glm.hpp>
#include <vector>

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

    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
