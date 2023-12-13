#pragma once
#include "IndexBuffer.h"
#include "ShapeFactory.h"
#include "VertexArray.h"
#include <glm/vec3.hpp>
#include <memory>
#include <string>
using std::shared_ptr;
using std::make_shared;

struct Material {
    Material(const char* diffuse_filepath,const char* specular_filepath,const unsigned int width,const unsigned int height):Diffuse(nullptr),Specular(nullptr){
        Diffuse=make_shared<Texture>(diffuse_filepath,width,height);
        Specular = make_shared<Texture>(specular_filepath,width,height);
    }
    Material(){}
    std::shared_ptr<Texture> Diffuse;
    std::shared_ptr<Texture> Specular;
};

class Model {
public:
    Model(std::string type);
    Model(std::string type,VAFlags flags);
    ~Model();
    //std::shared_ptr<Texture> m_Texture;
    void SetMaterial(const Material& material);
    std::string type;
    glm::vec3 position;
    float size;
    void Translate();
    void Scale();
    void Bind();
    void AssignTextures(const char* path, const unsigned int width, const unsigned int height);

private:
    VAFlags m_flags;
    bool texture_provided;
    void CreateDefaultTexture();
    void buildShape();
    void createBuffers();
   
   
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    std::shared_ptr<Material> m_DefaultMaterial;
    std::shared_ptr<Material> m_Material;
    std::shared_ptr<VertexArray> m_vertexArray;
};
