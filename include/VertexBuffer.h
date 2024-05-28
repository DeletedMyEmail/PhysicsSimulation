#pragma once

#include "../libs/glad/glad.h"

typedef struct {
    GLfloat x, y, z;
    GLfloat nx, ny, nz;
    GLfloat r, g, b, a;
} Vertex;

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const Vertex* pVertices, GLsizei pCount);
    ~VertexBuffer();

    void bind() const;
    static void unbind();

    GLsizei getCount() const;
private:
    GLsizei count;
    GLuint bufferID, vao;
};
