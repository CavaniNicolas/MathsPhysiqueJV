
#include "Render/VertexBufferLayout.hpp"

template <>
void VertexBufferLayout::push<float>(unsigned int count) {
  m_elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count) {
  m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count) {
  m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
