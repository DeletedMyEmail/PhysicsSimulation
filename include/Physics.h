#pragma once

#include <list>

#include "VerletParticle.h"
#include "Camera.h"

void applyForces(VerletParticle* pParticle);

void updateAndDraw(VerletParticle* pParticle, float pDeltaTime, const glm::mat4& pViewProj);

void handleConstrains(VerletParticle* pParticle, glm::vec3 pConstCenter, float pConstRadius);

void handleCollisions(const std::list<std::list<VerletParticle*>*>& pChunks, VerletParticle* pParticle);

void applyCentralForce(VerletParticle* pParticle);