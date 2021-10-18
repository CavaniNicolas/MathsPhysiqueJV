#pragma once

#include <vector>

#include "Render/VertexBuffer.hpp"

class Mesh
{
  private:
    const std::vector<Vertex>& m_vertices;
    const std::vector<unsigned int> m_indices;

  public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices);

    const std::vector<Vertex>& getVertices() const;

    const std::vector<unsigned int>& getIndices() const;
};
