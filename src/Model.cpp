#include "Model.h"

#include "vendor/imgui/imgui_impl_opengl3_loader.h"
#include <iostream>

Model::Model(std::string type) : m_type(type) { create_buffers(); }

Model::~Model() {}
void Model::Translate() {}
void Model::Scale() {}

void Model::create_buffers()
{
    
    if (m_type == "cube")
    {
        //Get vertices and indices
        std::vector<float> cubeVertices = ShapeFactory::create_cube();
        std::vector<unsigned int> cubeIndices = ShapeFactory::index_cube();
        //Create vertexbuffer and indexbuffer
        VertexBuffer* vbCube = new VertexBuffer(
            cubeVertices.data(), static_cast<unsigned int>(cubeVertices.size()));
        IndexBuffer cube_ib(cubeIndices.data(), cubeIndices.size());
        //create vertex array
        va = std::make_shared<VertexArray>(cubeVertices);
        //add the vertexbuffer. This function binds the vertex array, binds the 
        //binds the buffer, and assigns the attributes.
        va->AddBuffer(vbCube);
        //now bind the index buffer.
        cube_ib.Bind();
        //unbind and cleanup
        va->Unbind();
        vbCube->UnBind();
        delete vbCube;
    }
}
