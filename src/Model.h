#pragma once
#include "IndexBuffer.h"
#include "ShapeFactory.h"
#include "VertexArray.h"
#include <glm/vec3.hpp>
#include <memory>
#include <string>

class Model {
public:
  Model(std::string type);
  ~Model();
  std::string type;
  glm::vec3 position;
  float size;
  void Translate();
  void Scale();
  void Bind() { 
    m_Texture->Bind();
    m_vertexArray->Bind(); }
  void AddTextureImage(const char* path);

private:
  void buildShape();
  void createBuffers();
  std::vector<float> m_vertices;
  std::vector<unsigned int> m_indices;
  std::shared_ptr<VertexArray> m_vertexArray;
  std::shared_ptr<Texture> m_Texture;
};
