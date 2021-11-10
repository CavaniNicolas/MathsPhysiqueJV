
#include "Render/Mesh.hpp"

namespace render
{

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int> indices):
  m_vertices(vertices), m_indices(indices)
{
}

Mesh::Mesh(const Mesh& other): m_vertices(other.m_vertices), m_indices(other.m_indices) {}

const std::vector<Vertex>& Mesh::getVertices() const
{
    return m_vertices;
}

const std::vector<unsigned int>& Mesh::getIndices() const
{
    return m_indices;
}

} // namespace render
