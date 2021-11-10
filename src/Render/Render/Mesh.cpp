
#include "Render/Mesh.hpp"

namespace render
{

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int> indices): m_vertices(vertices), m_indices(indices)
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

Mesh& Mesh::operator=(const Mesh& other)
{
    if(this != &other)
    {
        m_vertices = other.m_vertices;
        m_indices = other.m_indices;
    }
    return *this;
}

} // namespace render
