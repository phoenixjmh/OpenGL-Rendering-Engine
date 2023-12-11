#include "Model.h"

#include "vendor/imgui/imgui_impl_opengl3_loader.h"
#include <iostream>

Model::Model(std::string type)
    : type(std::move(type))
{
    buildShape();
    createBuffers();
}

Model::~Model() = default;
void Model::Translate() { }
void Model::Scale() { }

void Model::AddTextureImage(const char* path){

  m_Texture = std::make_shared<Texture>(path);
}

void Model::buildShape()
{
    if (type == "cube") {
        m_vertices = ShapeFactory::create_cube();
        m_indices = ShapeFactory::index_cube();
    }
    if(type=="cube_no_index") {
      m_vertices = ShapeFactory::create_cube_no_index();
    }
    if (type == "plane") {
        m_vertices = ShapeFactory::create_plane();
    }
}

void Model::createBuffers()
{
    if (!m_indices.empty()) {
        VertexBuffer* vertex_buffer = new VertexBuffer(
            m_vertices.data(), static_cast<unsigned int>(m_vertices.size()));

        IndexBuffer index_buffer(m_indices.data(), m_indices.size());
        m_vertexArray = std::make_shared<VertexArray>();
        m_vertexArray->AddBuffer(vertex_buffer);
        index_buffer.Bind();
        m_vertexArray->Unbind();
        vertex_buffer->UnBind();
        delete vertex_buffer;
    } else {
        VertexBuffer* vertex_buffer = new VertexBuffer(
            m_vertices.data(), static_cast<unsigned int>(m_vertices.size()));
        m_vertexArray = std::make_shared<VertexArray>();
        m_vertexArray->AddBuffer(vertex_buffer);
        m_vertexArray->Unbind();
    }
}
