#include "../include/Model.h"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include <iostream>

Model::Model() : mesh(nullptr), shader(nullptr) {}

Model::Model(const Mesh* pMesh, const Shader* pShader) : mesh(pMesh), shader(pShader), matrix(glm::mat4(1.0f)), viewProjection(glm::mat4(1.0f)), viewProjectionLocation(-1) {
    viewProjectionLocation = glGetUniformLocation(pShader->getShaderId(), "u_modelViewProj");
}

void Model::rotate(const float pDegrees, const glm::vec3 pAxis) {
    matrix = glm::rotate(matrix, glm::radians(pDegrees), pAxis);
}

void Model::scale(const glm::vec3 pScale) {
    matrix = glm::scale(matrix, pScale);
}

void Model::draw() {
    shader->bind();
    glUniformMatrix4fv(viewProjectionLocation, 1, GL_FALSE, &viewProjection[0][0]);
    mesh->draw();
}

void Model::translate(const glm::vec3& pTranslation) {
    matrix = glm::translate(matrix, pTranslation);
}

glm::mat4& Model::getMatrix() {
    return matrix;
}

void Model::calModelViewProj(const glm::mat4& pViewProjection) {
    viewProjection = pViewProjection * matrix;
}

glm::mat4& Model::getViewProj() {
    return viewProjection;
}