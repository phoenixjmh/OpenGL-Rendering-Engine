#pragma once
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

 struct Texture{
   unsigned int id;
   string type;
   string path;
 };

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<Texture> Textures;

    void Draw(Shader& shader);
    unsigned int VAO;

private:
  /*  VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;*/
    unsigned int VBO,EBO;
    void setupMesh();
};
