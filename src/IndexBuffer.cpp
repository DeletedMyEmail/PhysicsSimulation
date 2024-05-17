#include "../include/IndexBuffer.h"

#include <iostream>

IndexBuffer::IndexBuffer() : count(0), bufferID(0) {}

IndexBuffer::IndexBuffer(const unsigned int* pIndices, const GLsizei pCount) : count(pCount), bufferID(0) {
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pCount * sizeof(unsigned int), pIndices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &bufferID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLsizei IndexBuffer::getCount() const {
    return count;
}
