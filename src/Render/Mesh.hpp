#pragma once

#include <vector>

#include "VertexBuffer.hpp"

class Mesh
{
private:
    const std::vector<Vertex>& m_vertices;
    const unsigned int* m_indices;

public:
    Mesh(const std::vector<Vertex>& vertices, const unsigned int* indices);

    const std::vector<Vertex>& getVertices() const;

    const unsigned int* getIndices() const;
};
