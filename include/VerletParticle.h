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
    glm::vec3 position;
    glm::vec3 prePosition;
    glm::vec3 acceleration;
    float radius;
    bool objIsStatic;

    Model* model;
};

std::vector<VerletParticle*>* createObjs(size_t pCount, float pObjRadius, float pSpawnRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);
VerletParticle* createParticle(glm::vec3 pPos, float pObjRadius, const char* pModelPath, const Shader* lShader);