
#pragma once

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
    unsigned int m_rendererID;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;
};
