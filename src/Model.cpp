#include "../include/Model.h"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include <iostream>

Model::Model(const Mesh* mesh, const Shader* shader) : mesh(mesh), shader(shader), matrix(glm::mat4(1.0f)) {
    matrixLocation = glGetUniformLocation(shader->getShaderId(), "u_model");
    if (matrixLocation == -1) {
        std::cout << "Could not find model matrix uniform location" << std::endl;
    }
}

void Model::rotate(float pDegrees, glm::vec3 pAxis) {
    matrix = glm::rotate(matrix, glm::radians(pDegrees), pAxis);
}

void Model::scale(glm::vec3 pScale) {
    matrix = glm::scale(matrix, pScale);
}

void Model::bind() {
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &matrix[0][0]);
    shader->bind();
    mesh->draw();
}
