#pragma once

#include "PhysicsObj.h"
#include "Camera.h"

#define G -1.8f
#define G_CENTRAL 5.0f

void applyForces(PhysicsObj pObj[], int pSize);

void updateAndDraw(PhysicsObj pObj[], int pSize, float pDeltaTime, Camera pCam);

void handleConstrains(PhysicsObj pObjs[], int pSize, glm::vec3 pConstCenter, float pConstRadius);

void handleCollisions(PhysicsObj pObj[], int pSize);

void applyCentralForce(PhysicsObj pObj[], int pSize);