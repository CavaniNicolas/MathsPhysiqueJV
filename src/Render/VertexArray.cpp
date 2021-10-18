
#include "Render/Renderer.hpp"
#include "Render/VertexArray.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        // specify the vertex layout
        GLCall(glEnableVertexAttribArray(i));
        // index i of the vertex array will be bound to the currently bound GL_ARRAY_BUFFER (it links the buffer with
        // the vao)
        GLCall(glVertexAttribPointer(
          i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
        ;
    }
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}
