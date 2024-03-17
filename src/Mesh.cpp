#include "Mesh.h"
using namespace Logger;

void Mesh::printTextureInfo()
{
    for (auto& tex : Textures) {
        Log("Texture: \n", "ID:", tex.id, "Path: ", tex.path, "Type: ", tex.type);
    }
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices
           , std::vector<Texture> textures) : Vertices(vertices), Indices(indices),
                                              Textures(textures) { setupMesh(); }

void Mesh::Draw(Shader& shader, unsigned int depthMap)
{
    unsigned int diffuse_nr = 1;
    unsigned int specular_nr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    unsigned int last_tex_id;
    unsigned int last_location = 0;
    // binding correct texture
    for (auto i = 0; i < Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = Textures[i].type;
        std::string material_name;
        if (name == "texture_diffuse") { number = std::to_string(diffuse_nr++); }
        else if (name == "texture_specular") { number = std::to_string(specular_nr++); }
        glUniform1i(glGetUniformLocation(shader.ID, ("material." + name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].id);
        last_location = GL_TEXTURE0 + i;
    }
    if (last_location == 0) Log("No textures bound");
    //add depth texture for shading
    // shader.setInt("UUID",30);
    shader.setInt("shadowMap", Textures.size());
    glActiveTexture(last_location + 1);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glActiveTexture(GL_TEXTURE0);
    m_vertexArray->Bind();
    if (!Indices.empty())
        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, Vertices.size());

    glBindVertexArray(0);
}

void Mesh::setupMesh()
{
#ifdef DEBUG_IMPORTER
    Log("Initializing Mesh buffers");
#endif

    if (!Indices.empty()) {
        VertexBuffer vertex_buffer(Vertices.data(), static_cast<unsigned int>(Vertices.size()));
        IndexBuffer index_buffer(Indices, Indices.size());
        m_vertexArray = new VertexArray(vertex_buffer);
        index_buffer.Bind();
        m_vertexArray->Unbind();
        vertex_buffer.UnBind();
    }
    else {
#ifdef DEBUG_IMPORTER
        Log("No Indices found, proceeding without IndexBuffer");
#endif
        VertexBuffer vertex_buffer(Vertices.data(), static_cast<unsigned int>(Vertices.size()));
        m_vertexArray = new VertexArray(vertex_buffer);
        m_vertexArray->Unbind();
        vertex_buffer.UnBind();
    }
}