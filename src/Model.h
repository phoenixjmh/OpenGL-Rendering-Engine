#pragma once
#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include "ShapeFactory.h";
#include "VertexArray.h"
#include "IndexBuffer.h"

class Model {
public:
    Model(std::string type);
    ~Model();

    std::string m_type;
    glm::vec3 position;
    float size;
    void Translate();
    void Scale();
    void Bind() { va->Bind(); }
    void create_buffers();
private:
    std::shared_ptr<VertexArray> va;

};
