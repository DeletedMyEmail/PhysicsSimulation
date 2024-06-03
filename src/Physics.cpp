#include "../include/Physics.h"

#include <list>

#include "../include/Constants.h"
#include "../include/Input.h"

void applyForces(VerletParticle* pParticle) {
    pParticle->applyForce(glm::vec3(0,G,0));

    if (KEY_STATES[GLFW_KEY_F])
        applyCentralForce(pParticle);
}

void updateAndDraw(VerletParticle* pParticle, const float pDeltaTime, Camera pCam) {
    pParticle->updatePos(pDeltaTime);
    pParticle->getModel()->calModelViewProj(pCam.getViewPorjection());
    pParticle->getModel()->draw();
}

void handleConstrains(VerletParticle* pParticle, const glm::vec3 pConstCenter, const float pConstRadius) {
    const glm::vec3 lToContiner = pConstCenter - pParticle->getPosition();
    const float lDist = glm::length(lToContiner);
    if (lDist + pParticle->getRadius() > pConstRadius) {
        const glm::vec3 lNorm = lToContiner / lDist;
        const glm::vec3 lDif = lNorm * (lDist + pParticle->getRadius() - pConstRadius);
        pParticle->getPosition() += lDif;
        pParticle->getModel()->translate(lDif);
    }
}

void handleCollisions(const std::list<std::list<VerletParticle*>*>& pChunks, VerletParticle* pParticle) {
    for (const std::list<VerletParticle*>* lChunk : pChunks) {
        for (VerletParticle* lParticle : *lChunk) {
            pParticle->collide(*lParticle);
        }
    }
}

void applyCentralForce(VerletParticle* pParticle) {
    const glm::vec3 lToContiner = glm::normalize(glm::vec3(0,0,0) - pParticle->getPosition());
    pParticle->applyForce(lToContiner * G_CENTRAL);
}