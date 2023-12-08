#pragma once
#include "VertexBuffer.h"
#include <glad/glad.h>
#include <vector>


class VertexArray {
public:
  VertexArray();
  ~VertexArray();
  void AddBuffer(VertexBuffer *buffer);
  void Bind();
  void Unbind();
  
private:
  unsigned int m_RendererID;
  VertexBuffer* vb;
};
