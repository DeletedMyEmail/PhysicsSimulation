#include "../include/VertexBuffer.h"
#include <cstddef>

VertexBuffer::VertexBuffer() : count(0), bufferID(0), vao(0) {}

VertexBuffer::VertexBuffer(const Vertex* pData, const GLsizei pCount) : count(pCount), bufferID(0), vao(0) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &bufferID);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*pCount, pData, GL_STATIC_DRAW);

    // specify position attribute for the shader
    // stride is offset between consecutive vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));

    unbind();
}

VertexBuffer::~VertexBuffer() {
    //glDeleteBuffers(1, &bufferID);
    if (vao != 0)
        glDeleteVertexArrays(1, &vao);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBindVertexArray(vao);
}

void VertexBuffer::unbind() {
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLsizei VertexBuffer::getCount() const {
    return count;
}
