#pragma once
#include <iostream>
#include <memory>
#include "stb_image/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/vec3.hpp>
#include <string>
//#include "vendor/imgui/imgui_impl_opengl3_loader.h"
#include "Mesh.h"
#include "ShapeFactory.h"

using std::make_shared;
using std::shared_ptr;

//struct Material {
//    Material(const char* diffuse_filepath, const char* specular_filepath,
//        const unsigned int width, const unsigned int height)
//        : Diffuse(nullptr)
//        , Specular(nullptr)
//    {
//        Diffuse = make_shared<Texture>(diffuse_filepath, width, height);
//        Specular = make_shared<Texture>(specular_filepath, width, height);
//    }
//    Material() { }
//    std::shared_ptr<Texture> Diffuse;
//    std::shared_ptr<Texture> Specular;
//};

class Model {
public:
    Model();
      ~Model();
    // std::shared_ptr<Texture> m_Texture;
    /*void SetMaterial(const Material& material);*/
    std::string type;
    glm::vec3 position;
    float size;
    void Draw(Shader& shader);
    void AssignTextures(const char* path, const unsigned int width,
        const unsigned int height);

private:
    VAFlags m_flags;
  /*  bool texture_provided;
    void CreateDefaultTexture();
    void buildShape();
    void createBuffers();

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    std::shared_ptr<Material> m_DefaultMaterial;
    std::shared_ptr<Material> m_Material;
    std::shared_ptr<VertexArray> m_vertexArray;*/

    // load model stuff
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> textures_loaded;
    void loadModel(const char* path);
    void processNode(aiNode* node, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string type_name);
    std::vector<Mesh> meshes;
    std::string directory;
};


