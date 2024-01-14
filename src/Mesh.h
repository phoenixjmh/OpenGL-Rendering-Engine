#pragma once
#include "IndexBuffer.h"
#include "Logger.h"
#include "Shader.h"
#include "VertexArray.h"
#include "glm/glm.hpp"
#include <string>
#include <vector>
using namespace Logger;

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<Texture> Textures;
    void Draw(Shader& shader, unsigned depthMap);
    void printTextureInfo();

private:
    VertexArray* m_vertexArray;
    void setupMesh();
};