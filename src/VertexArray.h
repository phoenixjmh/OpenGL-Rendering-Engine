#pragma once
#include "VertexBuffer.h"
#include <glad/glad.h>
#include <vector>

//#include "Texture.h"





struct VAFlags {
    VAFlags(): hasTexture(true){};
    bool hasTexture;
};

class VertexArray {
public:
  VertexArray(VAFlags flags);
  VertexArray();
  ~VertexArray()=default;
  void AddBuffer(VertexBuffer *buffer);
  void Bind();
  void Unbind();
  
private:

  VAFlags m_flags;
  unsigned int m_RendererID;
  VertexBuffer* vb;
};
