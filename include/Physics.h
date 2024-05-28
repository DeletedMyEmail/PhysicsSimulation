#pragma once

#include <forward_list>

#include "VerletObj.h"
#include "Camera.h"

#define G -9.81f
#define G_CENTRAL 15.0f

void applyForces(const std::forward_list<PhysicsObj*>& pObjs);

void updateAndDraw(const std::forward_list<PhysicsObj*>& pObjs, float pDeltaTime, Camera pCam);

void handleConstrains(const std::forward_list<PhysicsObj*>&pObjs, glm::vec3 pConstCenter, float pConstRadius);

void handleCollisions(const std::forward_list<PhysicsObj*>&pObjs);

void applyCentralForce(const std::forward_list<PhysicsObj*>&pObjs);