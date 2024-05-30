#pragma once

#include <forward_list>

#include "VerletParticle.h"
#include "Camera.h"

#define G -12.00f
#define G_CENTRAL 20.0f

void applyForces(const std::forward_list<VerletParticle*>& pObjs);

void updateAndDraw(const std::forward_list<VerletParticle*>& pObjs, float pDeltaTime, Camera pCam);

void handleConstrains(const std::forward_list<VerletParticle*>&pObjs, glm::vec3 pConstCenter, float pConstRadius);

void handleCollisions(const std::forward_list<VerletParticle*>&pObjs);

void applyCentralForce(const std::forward_list<VerletParticle*>&pObjs);