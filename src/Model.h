#pragma once
#include "stb_image/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/vec3.hpp>
#include <iostream>
#include <memory>
#include <string>
// #include "vendor/imgui/imgui_impl_opengl3_loader.h"
#include "Mesh.h"
#include "ShapeFactory.h"

class Model {
public:
    Model(const char* path, VAFlags flags);
    ~Model();
    glm::vec3 Position;
    float Size;

    void Draw(Shader& shader);
   
private:

    VAFlags m_flags;
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> textures_loaded;
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string type_name);
    std::vector<Mesh> m_Meshes;
    std::string m_ModelDirectory;

    void loadModel(const char* path);
    void processNode(aiNode* node, const aiScene* scene);
    void buildShape(); //used for non model-based loading
};

// Helper
static unsigned int TextureFromFile(const char* path, const std::string& directory,
    bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    std::cout << filename << "\n";

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
