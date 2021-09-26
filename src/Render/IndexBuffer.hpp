
#pragma once

class IndexBuffer
{
private:
    // index buffer object has to be unsigned ! (but can be char or short for memory savings
    unsigned int m_rendererID;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return m_count; }
};
