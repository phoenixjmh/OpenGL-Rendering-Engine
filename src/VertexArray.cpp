#include "VertexArray.h"


VertexArray::VertexArray(VertexBuffer vertex_buffer):vertexBuffer(vertex_buffer)
{
    VAFlags flags;
    flags.hasTexture = true;
    m_flags = flags;
    glGenVertexArrays(1, &m_RendererID);
    AddBuffer();
}

void VertexArray::AddBuffer()
{
    Bind(); //Bind self

    vertexBuffer.Bind(); 

    // tell our object how to navigate the vertex
    if (m_flags.hasTexture) {
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)offsetof(Vertex, Normal));

        glEnableVertexAttribArray(2);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)offsetof(Vertex, TexCoords));
    }
}


void VertexArray::Bind() { glBindVertexArray(m_RendererID); }
void VertexArray::Unbind() { glBindVertexArray(0); }
