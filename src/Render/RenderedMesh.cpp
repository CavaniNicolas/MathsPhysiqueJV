
// Include glm
#include <glm/gtc/matrix_transform.hpp>

#include "Render/RenderedMesh.hpp"

RenderedMesh::RenderedMesh(Mesh mesh, std::string textureFilepath)
    // TU UTILISES DES CONSTRUCTEURS PAR RECOPIE PAS BIENNNNNNNNN
    // Tu crees un buffer dont un glGenBuffer,
    // tu le donnes a m_vb avec la copie (Pareil pour m_va, m_ib et m_texture)
    // Et tu appelles le deleter de celui que tu as construit donc glDelete et
    // bam c'est nullllllllllllllll
    : m_va(),
      m_vb(mesh.getVertices()),
      // tu lui donne que "1" dans count x))))
      m_ib(mesh.getIndices().data(), mesh.getIndices().size()),
      m_layout(),
      m_texture(textureFilepath),
      m_model(glm::mat4(1.0f)) {
  m_layout.push<float>(3);
  m_layout.push<float>(2);
  m_va.addBuffer(m_vb, m_layout);

  //        std::cout << sizeof(indices)/sizeof(int) << std::endl;

  m_va.bind();
  m_ib.bind();
  m_texture.bind();  // bind parameter is 0 by default

  m_va.unbind();
}

void RenderedMesh::translate(glm::vec3 translation) {
  // translate the model
  m_model = glm::translate(glm::mat4(1.0f), translation);
}

void RenderedMesh::rotate(float rotation, glm::vec3 axis) {
  // rotate the model
  m_model = glm::rotate(m_model, glm::radians(rotation), axis);
}

void RenderedMesh::bind() const {
  m_va.bind();
  m_texture.bind();
}

void RenderedMesh::unbind() const {
  m_va.unbind();
  m_texture.unbind();
}

VertexArray& RenderedMesh::getVertexArray() { return m_va; }

VertexBuffer& RenderedMesh::getVertexBuffer() { return m_vb; }

IndexBuffer& RenderedMesh::getIndexBuffer() { return m_ib; }
