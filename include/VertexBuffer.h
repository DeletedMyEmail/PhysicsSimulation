#pragma once

#include "glad.h"
#include "Model.h"

class VertexBuffer {
public:
    VertexBuffer(const Vertex* pData, unsigned long pSize);
    ~VertexBuffer();
    void bind() const;
    static void unbind();
private:
    GLuint  bufferID, vao;
};
