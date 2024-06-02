#pragma once

#include <list>

#include "VerletParticle.h"
#include "Camera.h"

void applyForces(VerletParticle* pParticle);

void updateAndDraw(VerletParticle* pParticle, float pDeltaTime, Camera pCam);

void handleConstrains(VerletParticle* pParticle, glm::vec3 pConstCenter, float pConstRadius);

void handleCollisions(const std::list<VerletParticle*>& pParticlesInChunk, VerletParticle* pParticle);

void applyCentralForce(VerletParticle* pParticle);