#pragma once

#include <list>

#include "VerletParticle.h"
#include "Constants.h"

typedef struct ChunkPosition{
    size_t x, y, z;
    bool operator==(const ChunkPosition& pOther) const;
    inline bool operator!=(const ChunkPosition& chunk_position) const;
} ChunkPosition;

inline std::list<VerletParticle*> chunks[CHUNKS_PER_DIMENSION][CHUNKS_PER_DIMENSION][CHUNKS_PER_DIMENSION];
inline std::list<VerletParticle*> particles;

ChunkPosition getChunkPos(glm::vec3 pPos);
std::list<VerletParticle*>& getChunk(const ChunkPosition& pChunkPos);
void updateChunk(VerletParticle* pParticle, std::list<VerletParticle*>& pPrevChunk);
void spawnParticle(VerletParticle* pParticle);