#pragma once

#include <GL/glew.h>
#include <vector>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch(type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        //        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
  private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;

  public:
    VertexBufferLayout(): m_stride(0) {}

    template<typename T>
    void push(unsigned int count);

    inline std::vector<VertexBufferElement> const& getElements() const
    {
        return m_elements;
    }
    inline unsigned int getStride() const
    {
        return m_stride;
    }
};
