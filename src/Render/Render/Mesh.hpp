#pragma once

#include <vector>

#include "Render/VertexBuffer.hpp"

namespace render
{

class Mesh
{
  private:
    std::vector<Vertex>& m_vertices;
    std::vector<unsigned int> m_indices;

  public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int> indices);
    Mesh(const Mesh& other);

    const std::vector<Vertex>& getVertices() const;

    const std::vector<unsigned int>& getIndices() const;

    Mesh& operator=(const Mesh& other);
};

} // namespace render
