#pragma once
#include "glad.h"

class IndexBuffer {
public:
    IndexBuffer(const unsigned int* pIndices, unsigned int pSize);
    ~IndexBuffer();

    void bind() const;
    static void unbind();
private:
    GLuint bufferID;
};
