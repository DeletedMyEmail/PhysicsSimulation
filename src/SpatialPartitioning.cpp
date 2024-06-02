#include "../include/SpatialPartitioning.h"

#include <algorithm>
#include <iostream>
#include <list>

inline bool ChunkPosition::operator==(const ChunkPosition& pOther) const {
    return x == pOther.x && y == pOther.y && z == pOther.z;
}

inline bool ChunkPosition::operator!=(const ChunkPosition& chunk_position) const {
    return !(*this == chunk_position);
}

ChunkPosition getChunkPos(const glm::vec3 pPos) {
    return {
        static_cast<size_t>(pPos.x / CHUNK_SIZE + CHUNKS_PER_DIMENSION/2.0f),
        static_cast<size_t>(pPos.y / CHUNK_SIZE + CHUNKS_PER_DIMENSION/2.0f),
        static_cast<size_t>(pPos.z / CHUNK_SIZE + CHUNKS_PER_DIMENSION/2.0f)
    };
}

void updateChunk(VerletParticle* pParticle, std::list<VerletParticle*>& pPrevChunk) {
    auto& lNewChunk = getChunk(getChunkPos(pParticle->getPosition()));

    if (pPrevChunk == lNewChunk) return;

    pPrevChunk.remove(pParticle);
    lNewChunk.push_back(pParticle);
}

std::list<VerletParticle*>& getChunk(const ChunkPosition& pChunkPos) {
    return chunks[pChunkPos.x][pChunkPos.y][pChunkPos.z];
}

void spawnParticle(VerletParticle* pParticle) {
    const ChunkPosition lChunkPos = getChunkPos(pParticle->getPosition());
    chunks[lChunkPos.x][lChunkPos.y][lChunkPos.z].push_back(pParticle);
    particles.push_back(pParticle);
}