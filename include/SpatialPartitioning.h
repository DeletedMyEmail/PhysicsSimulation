#pragma once

#include <list>
#include <unordered_map>
#include "VerletParticle.h"
#include "Constants.h"

struct Vec3Hash {
    std::size_t operator()(const glm::vec3& vec) const {
        const std::size_t h1 = std::hash<float>()(vec.x);
        const std::size_t h2 = std::hash<float>()(vec.y);
        const std::size_t h3 = std::hash<float>()(vec.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

inline std::unordered_map<glm::vec3, std::list<VerletParticle*>, Vec3Hash> chunks(CHUNKS_PER_DIMENSION);
inline std::list<VerletParticle*> particles;

glm::vec3 getChunkPos(const glm::vec3& pPos);
std::list<std::list<VerletParticle*>*> getChunksInRadius(const glm::vec3& pChunkPos, const glm::vec3& pPos, float pRadius);
void updateChunk(VerletParticle* pParticle, std::list<VerletParticle*>& pPrevChunk);
void spawnParticle(VerletParticle* pParticle);