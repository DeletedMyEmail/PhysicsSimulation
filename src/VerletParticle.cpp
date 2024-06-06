#include "../include/VerletParticle.h"
#include "../include/Constants.h"
#include <ctime>

VerletParticle::VerletParticle(Model* pModel, const glm::vec3& pPosition, float pRadius) : mPosition(pPosition), mPrePosition(pPosition), mAcceleration(glm::vec3(0.0f)), mRadius(pRadius), mIsStatic(false), mModel(pModel) {
    mModel->translate(mPosition);
}

void VerletParticle::updatePos(const float pDeltaTime) {
    if (isStatic()) return;

    const glm::vec3 lVel = mPosition - mPrePosition;
    mPrePosition = mPosition;
    mPosition += lVel + mAcceleration * pDeltaTime * pDeltaTime;
    mAcceleration = glm::vec3(0.0f);

    mModel->translate(mPosition - mPrePosition);
}

void VerletParticle::applyForce(const glm::vec3& pForce) {
    if (isStatic()) return;
    mAcceleration += pForce;
}

void VerletParticle::setPosition(const glm::vec3& pPosition) {
    mPosition = pPosition;
}

Model* VerletParticle::getModel() const {
    return mModel;
}

glm::vec3& VerletParticle::getPosition() {
    return mPosition;
}

glm::vec3& VerletParticle::getPrevPosition() {
    return mPrePosition;
}

float VerletParticle::getRadius() const {
    return mRadius;
}

void VerletParticle::collide(VerletParticle& pOther) {
    if (isStatic() || this == &pOther) return;

    const glm::vec3 lColAxis = mPosition - pOther.mPosition;
    const float lDist = glm::length(lColAxis);

    const float lDelta = mRadius + pOther.getRadius() - lDist;
    if (lDelta <= 0) return;

    const glm::vec3 lNorm = lColAxis / lDist;
    const glm::vec3 lPosDiff = lNorm * lDelta * COLLISION_DAMPING;

    mPosition += lPosDiff;
    mModel->translate(lPosDiff);
    if (!pOther.isStatic()) {
        pOther.getPosition() -= lPosDiff;
        pOther.getModel()->translate(-lPosDiff);
    }
}

void VerletParticle::move(const glm::vec3& pTranslation) {
    mModel->translate(pTranslation);
    mPosition += pTranslation;
    mPrePosition += pTranslation;
}

void VerletParticle::setStatic(const bool pIsStatic) {
    mIsStatic = pIsStatic;
}

bool VerletParticle::isStatic() const {
    return mIsStatic;
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

