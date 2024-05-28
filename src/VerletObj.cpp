#include "../include/PhysicsObj.h"

PhysicsObj::PhysicsObj(Model* pModel, const glm::vec3& pPosition, float pRadius) : position(pPosition), prePosition(pPosition), acceleration(glm::vec3(0.0f)), radius(pRadius), objIsStatic(false), model(pModel) {
    model->translate(position);
}

void PhysicsObj::updatePos(const float pDeltaTime) {
    if (isStatic()) return;

    const glm::vec3 lVel = position - prePosition;
    prePosition = position;
    position += lVel + acceleration * pDeltaTime * pDeltaTime;
    acceleration = glm::vec3(0.0f);

    model->translate(position - prePosition);
}

void PhysicsObj::applyForce(const glm::vec3& pForce) {
    if (isStatic()) return;
    acceleration += pForce;
}

void PhysicsObj::setPosition(const glm::vec3& pPosition) {
    position = pPosition;
}

Model* PhysicsObj::getModel() const {
    return model;
}

glm::vec3& PhysicsObj::getPosition() {
    return position;
}

float PhysicsObj::getRadius() const {
    return radius;
}

void PhysicsObj::collide(PhysicsObj& pOther) {
    if (isStatic() || this == &pOther) return;

    const glm::vec3 lColAxis = position - pOther.position;
    const float lDist = glm::length(lColAxis);

    if (lDist >= radius + pOther.getRadius()) return;

    glm::vec3 lNorm = lColAxis / lDist;
    float lDelta = radius + pOther.getRadius() - lDist;

    position += lNorm * lDelta * 0.5f;
    if (!pOther.isStatic())
        pOther.getPosition() -= lNorm * lDelta * 0.5f;
}

void PhysicsObj::move(const glm::vec3& pTranslation) {
    model->translate(pTranslation);
    position += pTranslation;
    prePosition += pTranslation;
}

void PhysicsObj::setStatic(const bool pIsStatic) {
    objIsStatic = pIsStatic;
}

bool PhysicsObj::isStatic() const {
    return objIsStatic;
}
