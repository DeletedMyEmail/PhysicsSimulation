#include "../include/VertexBuffer.h"
#include <cstddef>

VertexBuffer::VertexBuffer() : count(0), bufferID(0), vao(0) {}

VertexBuffer::VertexBuffer(const Vertex* pVertices, const GLsizei pCount) : count(pCount), bufferID(0), vao(0) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &bufferID);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*pCount, pVertices, GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    // normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, nx)));
    // color attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));

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
