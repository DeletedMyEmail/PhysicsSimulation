#pragma once

#include "../libs/glad/glad.h"

class IndexBuffer {
public:
    IndexBuffer();
    IndexBuffer(const unsigned int* pIndices, GLsizei pCount);
    ~IndexBuffer();

    void bind() const;
    static void unbind();

    GLsizei getCount() const;
private:
    GLsizei count;
    GLuint bufferID;
};
