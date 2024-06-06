#pragma once

#include "Model.h"

class VerletParticle {
public:
    VerletParticle() = default;
    VerletParticle(Model* model, const glm::vec3& pPosition, float pRadius);
    void updatePos(float pDeltaTime);
    void applyForce(const glm::vec3& pForce);
    void collide(VerletParticle& pOther);
    void move(const glm::vec3& pTranslation);

    void setStatic(bool pIsStatic);
    bool isStatic() const;
    void setPosition(const glm::vec3& pPosition);
    Model* getModel() const;
    glm::vec3& getPosition();
    glm::vec3& getPrevPosition();
    float getRadius() const;
private:
    glm::vec3 mPosition;
    glm::vec3 mPrePosition;
    glm::vec3 mAcceleration;
    float mRadius;
    bool mIsStatic;

    Model* mModel;
};

VerletParticle* createParticle(glm::vec3 pPos, float pObjRadius, const char* pModelPath, const Shader* lShader);