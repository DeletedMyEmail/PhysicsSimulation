#pragma once

#include "Model.h"

class PhysicsObj {
public:
    PhysicsObj() = default;
    PhysicsObj(Model* model, const glm::vec3& pPosition, float pRadius);
    void updatePos(float pDeltaTime);
    void applyForce(const glm::vec3& pForce);
    void collide(PhysicsObj& pOther);
    void move(const glm::vec3& pTranslation);

    void setStatic(bool pIsStatic);
    bool isStatic() const;
    void setPosition(const glm::vec3& pPosition);
    Model* getModel() const;
    glm::vec3& getPosition();
    float getRadius() const;
private:
    glm::vec3 position;
    glm::vec3 prePosition;
    glm::vec3 acceleration;
    float radius;
    bool objIsStatic;

    Model* model;
};
