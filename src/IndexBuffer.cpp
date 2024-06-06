#include "../include/IndexBuffer.h"

IndexBuffer::IndexBuffer() : mIndexCount(0), mBufferID(0) {}

IndexBuffer::IndexBuffer(const unsigned int* pIndices, const GLsizei pCount) : mIndexCount(pCount), mBufferID(0) {
    glGenBuffers(1, &mBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pCount * sizeof(unsigned int), pIndices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    if (mBufferID != 0)
        glDeleteBuffers(1, &mBufferID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLsizei IndexBuffer::getCount() const {
    return mIndexCount;
}
