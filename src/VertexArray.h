#pragma once
#include "VertexBuffer.h"
#include <glad/glad.h>
#include <vector>

//#include "Texture.h"





struct VAFlags {
      bool hasTexture;
  PrimitiveShape shape;
};

class VertexArray {
public:
  VertexArray(VAFlags flags);
  VertexArray(VertexBuffer vertex_buffer);
  ~VertexArray()=default;
  void AddBuffer();
  void Bind();
  void Unbind();
  
private:

  VAFlags m_flags;
  unsigned int m_RendererID;
  VertexBuffer vb;
};
