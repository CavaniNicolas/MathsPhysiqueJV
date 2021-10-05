#pragma once

#include <GL/glew.h>

#include "Render/Camera.hpp"
#include "Render/IndexBuffer.hpp"
#include "Render/RenderedMesh.hpp"
#include "Render/Shader.hpp"
#include "Render/VertexArray.hpp"

// MSVC macro to break the program (windows only)
#define ASSERT(x) if (!(x)) __debugbreak();

// macro to wrap opengl functions to assert errors without having to wrap the
// functions ourselves
#define GLCall(x) \
  GLClearError(); \
  x;              \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
 public:
  void clear() const;
  void draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
  void draw(Shader& shader, Camera& camera, RenderedMesh& rendMesh) const;
};
