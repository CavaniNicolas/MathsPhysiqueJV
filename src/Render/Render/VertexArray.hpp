#pragma once

#include "Render/VertexBuffer.hpp"
#include "Render/VertexBufferLayout.hpp"

class VertexArray
{
  private:
    unsigned int m_rendererID;

  public:
    VertexArray();
    ~VertexArray();

    // We dont want to be able to copy as we simply handle it using an int
    // for the moment, and not a memory address to the actual opengl object
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;
};
