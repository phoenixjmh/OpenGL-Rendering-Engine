#include "VertexArray.h"
VertexArray::VertexArray(VAFlags flags)
    : m_flags(flags)

{
    glGenVertexArrays(1, &m_RendererID);
}
VertexArray::~VertexArray()
{
    // glDeleteVertexArrays(1,&m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer* buffer)
{
    Bind();
    vb = buffer;
    vb->Bind();
    // tell our object how to navigate the vertex
    if (m_flags.hasTexture) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

    } else {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
            (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    if (m_flags.hasTexture) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}

void VertexArray::Bind() { glBindVertexArray(m_RendererID); }
void VertexArray::Unbind() { glBindVertexArray(0); }
