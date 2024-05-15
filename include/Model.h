#pragma once

#include <GLFW/glfw3.h>

typedef struct {
    GLfloat x, y, z;
    GLfloat r, g, b;
} Vertex;

class Model {
public:
    Model();
private:
    Vertex* vertices;
    GLuint* verticesSize;
};
