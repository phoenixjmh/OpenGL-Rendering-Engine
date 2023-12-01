#include "VertexArray.h"

VertexArray::VertexArray(std::vector<float> vertices)

{
    glGenVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer* buffer)
{
    Bind();
    vb = buffer;
    vb->Bind();
    //tell our object how to navigate the vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void VertexArray::Bind()
{
    glBindVertexArray(m_RendererID);
}
void VertexArray::Unbind()
{
    glBindVertexArray(0);
}
