#include "../include/Physics.h"

void applyForces(const std::forward_list<PhysicsObj*>& pObjs) {
    for (PhysicsObj* lObj : pObjs) {
        lObj->applyForce(glm::vec3(0,G,0));
    }
}

void updateAndDraw(const std::forward_list<PhysicsObj*>& pObjs, const float pDeltaTime, Camera pCam) {
    for (PhysicsObj* lObj : pObjs) {
        lObj->updatePos(pDeltaTime);
        lObj->getModel()->calModelViewProj(pCam.getViewPorjection());
        lObj->getModel()->draw();
    }
}

void handleConstrains(const std::forward_list<PhysicsObj*>& pObjs, const glm::vec3 pConstCenter, const float pConstRadius) {
    for (PhysicsObj* lObj : pObjs) {
        glm::vec3 lToContiner = pConstCenter - lObj->getPosition();
        float lDist = glm::length(lToContiner);
        if ((lDist + lObj->getRadius()) > pConstRadius) {
            glm::vec3 lNorm = lToContiner / lDist;
            glm::vec3 lDif = lNorm * (lDist + lObj->getRadius() - pConstRadius);
            lObj->getPosition() += lDif;
            lObj->getModel()->translate(lDif);
        }
    }
}

void handleCollisions(const std::forward_list<PhysicsObj*>& pObjs) {
    for (PhysicsObj* lObj : pObjs) {
        for (PhysicsObj* lObj2 : pObjs) {
            lObj->collide(*lObj2);
        }
    }
}

void applyCentralForce(const std::forward_list<PhysicsObj*>& pObjs) {
    for (PhysicsObj* lObj : pObjs) {
        glm::vec3 lToContiner = glm::normalize(glm::vec3(0,0,0) - lObj->getPosition());
        lObj->applyForce(lToContiner * G_CENTRAL);
    }
}