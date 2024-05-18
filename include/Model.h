#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "../libs/glm/glm.hpp"

class Model {
public:
    Model(const Mesh* mesh, const  Shader* shader);
    void rotate(float pDegrees, glm::vec3 pAxis);
    void scale(glm::vec3 pScale);
    void bind();
private:
    const Mesh* mesh;
    const Shader* shader;
    glm::mat4 matrix;
    int matrixLocation;
};
