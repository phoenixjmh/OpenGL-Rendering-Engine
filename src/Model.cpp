#include "Model.h"



unsigned int TextureFromFile(const char* path, const std::string& directory,
    bool gamma = false);
Model::Model(const char* path, VAFlags flags)
    : m_flags(flags)
    , name(path)
{

    if (m_flags.shape == PrimitiveShape::NONE)
    {
        stbi_set_flip_vertically_on_load(true);
        loadModel(path);
    }
    else
    {
        buildShape();
    }
#ifdef DEBUG_IMPORT
    printDebugInfo();

#endif
}
void Model::printDebugInfo()
{
    for (auto& mesh : m_Meshes)
    {
        Log("Model", name);
        mesh.printTextureInfo();
    }
}
void Model::Draw(Shader& shader, unsigned int depthMap)
{
    for (auto& mesh : m_Meshes)
    {
        mesh.Draw(shader, depthMap);
    }
}

void Model::loadModel(const char* path)
{
    std::string filepath =  static_cast<std::string>(path);
    Assimp::Importer import;
    const aiScene * scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << "\n";
        return;
    }
    m_ModelDirectory = filepath.substr(0, filepath.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
    std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), m_ModelDirectory);
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

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
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
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 tex = { mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y };
            vertex.TexCoords = tex;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuse_maps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

    std::vector<Texture> specular_maps = loadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

    std::vector<Texture> normal_maps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

    std::vector<Texture> height_maps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), height_maps.begin(), height_maps.end());

    // we need normal and height maps
    return { vertices, indices, textures };
}

Model::~Model() = default;

void Model::buildShape()
{
    if (m_flags.shape == CUBE)
    {
        std::vector<Vertex> cube_verts = ShapeFactory::create_cube_no_index();
        std::vector<Texture> textures;

        const Texture diffuse = { TextureFromFile("../../textures/wood.png", "../../textures/wood.png"), (std::string)"texture_diffuse", (std::string)"textures/wood.png" };
        const Texture specular = { TextureFromFile("../../textures/wood-spec.png", "../../textures/wood-spec.png"), (std::string)"texture_specular", (std::string)"textures/wood-spec.png" };
        textures.push_back(diffuse);
        textures.push_back(specular);

        // dummy indices
        std::vector<unsigned int> indices;
        Mesh cube(cube_verts, indices, textures);
        m_Meshes.push_back(cube);
    }
}
