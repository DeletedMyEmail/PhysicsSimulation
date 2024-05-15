#include "../include/VertexBuffer.h"
#include <cstddef>

VertexBuffer::VertexBuffer(const Vertex* pData, const unsigned long pSize) : bufferID(0), vao(0) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &bufferID);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*pSize, pData, GL_STATIC_DRAW);

    // specify position attribute for the shader
    // stride is offset between consecutive vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &bufferID);
    glDeleteVertexArrays(1, &vao);
}

void VertexBuffer::bind() const {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

void VertexBuffer::unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}