#include "Model.h"

#include "vendor/imgui/imgui_impl_opengl3_loader.h"
#include <iostream>

#define LOG(x) std::cout << x << "\n";

Model::Model(std::string type)
    : type(std::move(type))
    , texture_provided(false)
{
    m_Material =std::make_shared<Material>();
    m_DefaultMaterial = std::make_shared<Material>();
    CreateDefaultTexture();
    buildShape();
    createBuffers();
}
Model::Model(std::string type, VAFlags flags)
    : type(std::move(type))
    , texture_provided(false)
    , m_flags(flags)
{
    buildShape();
    createBuffers();
}

Model::~Model() = default;
void Model::Translate() { }
void Model::Scale() { }
void Model::CreateDefaultTexture()
{
    const char* filepath = "textures/TEST.png";
    const unsigned int width = 250;
    const unsigned int height = 250;
    // Change to default "MATERIAL"
    m_DefaultMaterial->Diffuse = make_shared<Texture>(filepath, width, height);
    LOG("Created default tex");
}

void Model::Bind()
{
    if (m_flags.hasTexture) {
        if (texture_provided) {
            glActiveTexture(GL_TEXTURE0);
            m_Material->Diffuse->Bind();
            glActiveTexture(GL_TEXTURE1);
            m_Material->Specular->Bind();

        } else {
            glActiveTexture(GL_TEXTURE0);
            m_DefaultMaterial->Diffuse->Bind();
            LOG("Bound Default");
        }
    }
    //LOG("TEX BOUND")
    m_vertexArray->Bind();
}

void Model::SetMaterial(const Material& material)
{
    *m_Material=material;
    texture_provided=true;
}



void Model::buildShape()
{
    if (type == "cube") {
        m_vertices = ShapeFactory::create_cube();
        m_indices = ShapeFactory::index_cube();
    }
    if (type == "cube_no_index") {
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

        m_vertexArray = std::make_shared<VertexArray>(m_flags);
        m_vertexArray->AddBuffer(vertex_buffer);
        index_buffer.Bind();
        m_vertexArray->Unbind();
        vertex_buffer->UnBind();
        delete vertex_buffer;
    } else {
        VertexBuffer* vertex_buffer = new VertexBuffer(
            m_vertices.data(), static_cast<unsigned int>(m_vertices.size()));
        m_vertexArray = std::make_shared<VertexArray>(m_flags);
        m_vertexArray->AddBuffer(vertex_buffer);
        m_vertexArray->Unbind();
    }
}
