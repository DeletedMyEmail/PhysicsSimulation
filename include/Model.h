#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "../libs/glm/glm.hpp"

class Model {
public:
    Model();
    Model(const Mesh* mesh, const  Shader* shader);
    void rotate(float pDegrees, glm::vec3 pAxis);
    void scale(glm::vec3 pScale);
    void bind();

    void translate(const glm::vec3& pTranslation);

    void calModelViewProj(const glm::mat4& pViewProjection);
    glm::mat4& getMatrix();
    glm::mat4& getViewProj();
private:
    const Mesh* mesh;
    const Shader* shader;
    glm::mat4 matrix;
    glm::mat4 viewProjection;
    int viewProjectionLocation;
};
