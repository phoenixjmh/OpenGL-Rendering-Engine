#pragma once
#include "glm/glm.hpp"
enum PrimitiveShape{NONE,PLANE,CUBE,SPHERE};

 struct Vertex{
  Vertex(glm::vec3 pos,glm::vec3 norm,glm::vec2 texCoord):
  Position(pos),
  Normal(norm),
  TexCoords(texCoord){}
  Vertex(){}
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
