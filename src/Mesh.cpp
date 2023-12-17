#include "Mesh.h"
using namespace Logger;

void printTextureInfo(std::vector<Texture> textures)
{
    for (auto& tex : textures)
    {
        Log("Texture: \n","ID:",tex.id,"Path: ", tex.path,"Type: ", tex.type);
    }
}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
    std::vector<Texture> textures)
    : Vertices(vertices)
    , Indices(indices)
    , Textures(textures)
{
    Log("Mesh Class:","\nVertices found:",vertices.size(),"\nIndices found:",indices.size(),"\nTextures found:",textures.size());
    printTextureInfo(textures);
    setupMesh();
}

void Mesh::Draw(Shader& shader)
{
    unsigned int diffuse_nr = 1;
    unsigned int specular_nr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (auto i = 0; i < Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = Textures[i].type;
        std::string material_name;
        if (name == "texture_diffuse") {
            material_name = "material.diffuse";
            number = std::to_string(diffuse_nr++);
            glUniform1i(glGetUniformLocation(shader.ID, (material_name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, Textures[i].id);
        } else if (name == "texture_specular") {
            material_name="material.specular";
            number = std::to_string(specular_nr++);
            glUniform1i(glGetUniformLocation(shader.ID, (material_name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, Textures[i].id);
            
        }
    }
 
       glActiveTexture(GL_TEXTURE0);

    m_vertexArray->Bind();
    if (Indices.size() > 0)
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(Indices.size()), GL_UNSIGNED_INT, 0);
    else {
        glDrawArrays(GL_TRIANGLES, 0, static_cast<unsigned int>(Vertices.size()));
    }

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupMesh()
{
    Log("Initializing Mesh buffers");
    if (Indices.size() > 0) {
        VertexBuffer m_vertexBuffer(Vertices.data(), static_cast<unsigned int>(Vertices.size()));
        IndexBuffer index_buffer(Indices, Indices.size());
        m_vertexArray = new VertexArray(m_vertexBuffer);
        index_buffer.Bind();
        m_vertexArray->Unbind();
        m_vertexBuffer.UnBind();
    } else {
        Log("No Indices found, proceeding without IndexBuffer");
        VertexBuffer m_vertexBuffer(Vertices.data(), static_cast<unsigned int>(Vertices.size()));
        m_vertexArray = new VertexArray(m_vertexBuffer);
        m_vertexArray->Unbind();
        m_vertexBuffer.UnBind();
    }
}
