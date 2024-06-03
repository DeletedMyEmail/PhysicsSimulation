#include "../include/VerletParticle.h"
#include "../include/Constants.h"
#include <ctime>

VerletParticle::VerletParticle(Model* pModel, const glm::vec3& pPosition, float pRadius) : position(pPosition), prePosition(pPosition), acceleration(glm::vec3(0.0f)), radius(pRadius), objIsStatic(false), model(pModel) {
    model->translate(position);
}

void VerletParticle::updatePos(const float pDeltaTime) {
    if (isStatic()) return;

    const glm::vec3 lVel = position - prePosition;
    prePosition = position;
    position += lVel + acceleration * pDeltaTime * pDeltaTime;
    acceleration = glm::vec3(0.0f);

    model->translate(position - prePosition);
}

void VerletParticle::applyForce(const glm::vec3& pForce) {
    if (isStatic()) return;
    acceleration += pForce;
}

void VerletParticle::setPosition(const glm::vec3& pPosition) {
    position = pPosition;
}

Model* VerletParticle::getModel() const {
    return model;
}

glm::vec3& VerletParticle::getPosition() {
    return position;
}

glm::vec3& VerletParticle::getPrevPosition() {
    return prePosition;
}

float VerletParticle::getRadius() const {
    return radius;
}

void VerletParticle::collide(VerletParticle& pOther) {
    if (isStatic() || this == &pOther) return;

    const glm::vec3 lColAxis = position - pOther.position;
    const float lDist = glm::length(lColAxis);

    if (lDist >= radius + pOther.getRadius()) return;

    const glm::vec3 lNorm = lColAxis / lDist;
    const float lDelta = radius + pOther.getRadius() - lDist;
    const glm::vec3 lPosDiff = lNorm * lDelta * COLLISION_DAMPING;

    position += lPosDiff;
    model->translate(lPosDiff);
    if (!pOther.isStatic()) {
        pOther.getPosition() -= lPosDiff;
        pOther.getModel()->translate(-lPosDiff);
    }
}

void VerletParticle::move(const glm::vec3& pTranslation) {
    model->translate(pTranslation);
    position += pTranslation;
    prePosition += pTranslation;
}

void VerletParticle::setStatic(const bool pIsStatic) {
    objIsStatic = pIsStatic;
}

bool VerletParticle::isStatic() const {
    return objIsStatic;
}

std::vector<VerletParticle*>* createObjs(const size_t pCount, const float pObjRadius, const float pSpawnRadius,
                                         const char* pVertexPath, const char* pFragPath, const char* pModelPath) {
    const Shader* lShader = new Shader(pVertexPath, pFragPath);
    auto* lParticle = new std::vector<VerletParticle*>;

    srand(time(nullptr));
    for (int i = 0; i < pCount; i++) {
        const auto lMesh = new Mesh(pModelPath);
        const auto lModel =  new Model(lMesh, lShader);
        lModel->scale(glm::vec3(pObjRadius));

        auto lPos = glm::vec3(rand(), rand(), rand());
        lPos = glm::normalize(lPos) * (0.0f + rand() % static_cast<int>(pSpawnRadius - pObjRadius));

        lParticle[i].push_back(new VerletParticle(lModel, lPos, pObjRadius));
    }

    return lParticle;
}

VerletParticle* createParticle(const glm::vec3 pPos, const float pObjRadius, const char* pModelPath, const Shader* lShader) {
    const auto lMesh = new Mesh(pModelPath, 1.0f);
    const auto lModel =  new Model(lMesh, lShader);
    lModel->scale(glm::vec3(pObjRadius));

    return new VerletParticle(lModel, pPos, pObjRadius);
}

