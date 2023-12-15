﻿#include "Model.h"

#define LOG(x) std::cout << x << "\n";

unsigned int TextureFromFile(const char* path, const string& directory,
    bool gamma = false);
Model::Model(const char* path, VAFlags flags)
    : m_flags(flags)
{

    if (m_flags.shape == PrimitiveShape::NONE) {

        stbi_set_flip_vertically_on_load(true);
        loadModel(path);
    } else {

        buildShape();
    }
}

void Model::Draw(Shader& shader)
{
    for (auto& mesh : meshes) {
        // std::cout<<"Call to mesh"<<"\n";
        mesh.Draw(shader);
    }
}

void Model::loadModel(const char* path)
{
    std::string filepath = "../../" + static_cast<std::string>(path);
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
        return;
    }
    directory = filepath.substr(0, filepath.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        std::cout << "Found mesh\n";
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
    string typeName)
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) {
            // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        glm::vec3 positions;

        positions.x = mesh->mVertices[i].x;
        positions.y = mesh->mVertices[i].y;
        positions.z = mesh->mVertices[i].z;

        vertex.Position = positions;
        glm::vec3 normals = {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z,
        };
        vertex.Normal = normals;
        if (mesh->mTextureCoords[0]) {
            glm::vec2 tex = { mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y };
            vertex.TexCoords = tex;
        } else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        // std::cout<<"POSITIONS"<<vertex.TexCoords.x<<vertex.TexCoords.y<<"\n";

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    vector<Texture> specularMaps = loadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // we need normal and height maps
    return Mesh(vertices, indices, textures);
}

unsigned int TextureFromFile(const char* path, const string& directory,
    bool gamma)
{
    string filename = string(path);
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

Model::~Model() = default;

void Model::buildShape()
{
    if (m_flags.shape == CUBE) {
        vector<Vertex> cube_verts = ShapeFactory::create_cube_no_index();
        vector<Texture> textures;

        const Texture diffuse = { TextureFromFile("../../textures/wood.png", "../../textures/wood.png"), (std::string) "texture_diffuse", (std::string) "textures/wood.png" };
        const Texture specular = { TextureFromFile("../../textures/wood-spec.png", "../../textures/wood-spec.png"), (std::string) "texture_specular", (std::string) "textures/wood-spec.png" };
        textures.push_back(diffuse);
        textures.push_back(specular);

        // dummy indices
        vector<unsigned int> indices;
        Mesh cube(cube_verts, indices, textures);
        meshes.push_back(cube);
    }
}
