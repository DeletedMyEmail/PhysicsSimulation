#pragma once

#include "../libs/glad/glad.h"

typedef struct {
    GLfloat x, y, z;
    GLfloat r, g, b, a;
} Vertex;

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const Vertex* pData, GLsizei pCount);
    ~VertexBuffer();

    void bind() const;
    static void unbind();

    GLsizei getCount() const;
private:
    GLsizei count;
    GLuint bufferID, vao;
};
