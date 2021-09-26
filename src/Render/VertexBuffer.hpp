
#pragma once

class VertexBuffer
{
private:
    // index buffer object has to be unsigned ! (but can be char or short for memory savings
    unsigned int m_rendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
