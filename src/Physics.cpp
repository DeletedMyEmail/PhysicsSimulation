#include "../include/Physics.h"

void applyForces(PhysicsObj pObj[], const int pSize) {
    for (int i = 0; i < pSize; i++) {
        pObj[i].applyForce(glm::vec3(0,G,0));
    }
}

void updateAndDraw(PhysicsObj pObj[], const int pSize, const float pDeltaTime, Camera pCam) {
    for (int i = 0; i < pSize; i++) {
        //std::cout << pObj[i].getPosition().x << " " << pObj[i].getPosition().y << " " << pObj[i].getPosition().z << std::endl;
        pObj[i].updatePos(pDeltaTime);
        pObj[i].getModel()->calModelViewProj(pCam.getViewPorjection());
        pObj[i].getModel()->draw();
    }
}

void handleConstrains(PhysicsObj pObjs[], const int pSize, const glm::vec3 pConstCenter, const float pConstRadius) {
    for (int i = 0; i < pSize; i++) {
        glm::vec3 lToContiner = pConstCenter - pObjs[i].getPosition();
        float lDist = glm::length(lToContiner);
        if ((lDist + pObjs[i].getRadius()) > pConstRadius) {
            glm::vec3 lNorm = lToContiner / lDist;
            pObjs[i].getPosition() = pConstCenter - lNorm * (pConstRadius - pObjs[i].getRadius());
        }
    }
}

void handleCollisions(PhysicsObj pObj[], const int pSize) {
    for (int i = 0; i < pSize; i++) {
        for (int j = 0; j < pSize; j++) {
            pObj[i].collide(pObj[j]);
        }
    }
}

void applyCentralForce(PhysicsObj pObj[], const int pSize) {
    for (int i = 0; i < pSize; i++) {
        glm::vec3 lToContiner = glm::normalize(glm::vec3(0,0,0) - pObj[i].getPosition());
        pObj[i].applyForce(lToContiner * G_CENTRAL);
    }
}