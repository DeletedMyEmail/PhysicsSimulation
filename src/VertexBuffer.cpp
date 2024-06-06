#include "../include/VertexBuffer.h"
#include <cstddef>
#include <iostream>

VertexBuffer::VertexBuffer() : mVertCount(0), mBufferID(0), mVaoID(0) {}

VertexBuffer::VertexBuffer(const Vertex* pVertices, const GLsizei pCount) : mVertCount(pCount), mBufferID(0), mVaoID(0) {
    glGenVertexArrays(1, &mVaoID);
    glGenBuffers(1, &mBufferID);

    glBindVertexArray(mVaoID);

    glBindBuffer(GL_ARRAY_BUFFER, mBufferID);
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VertexBuffer::~VertexBuffer() {
    //glDeleteBuffers(1, &bufferID);
    if (mVaoID != 0)
        glDeleteVertexArrays(1, &mVaoID);
}

void VertexBuffer::bind() const {
    //glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBindVertexArray(mVaoID);
}

void VertexBuffer::unbind() {
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLsizei VertexBuffer::getCount() const {
    return mVertCount;
}
