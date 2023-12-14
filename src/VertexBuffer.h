#pragma once
#include "glm/glm.hpp"

 struct Vertex{
   glm::vec3 Position;
   glm::vec3 Normal;
   glm::vec2 TexCoords;

 };
class VertexBuffer {
public:
  VertexBuffer(const void *data, unsigned int size );
  ~VertexBuffer();
  void Bind();
  void UnBind();

private:
  unsigned int m_RendererID;
};
