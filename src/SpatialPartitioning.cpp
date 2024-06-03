#include "../include/SpatialPartitioning.h"
#include <iostream>
#include <list>

glm::vec3 getChunkPos(const glm::vec3 pPos) {
    return {
        std::floor(pPos.x / CHUNK_SIZE),
        std::floor(pPos.y / CHUNK_SIZE),
        std::floor(pPos.z / CHUNK_SIZE)
    };
}

void updateChunk(VerletParticle* pParticle, std::list<VerletParticle*>& pPrevChunk) {
    std::list<VerletParticle*>& lNewChunk = chunks[getChunkPos(pParticle->getPosition())];

    if (pPrevChunk == lNewChunk) return;

    pPrevChunk.remove(pParticle);
    lNewChunk.push_back(pParticle);
}

void spawnParticle(VerletParticle* pParticle) {
    const glm::vec3 lChunkPos = getChunkPos(pParticle->getPosition());
    chunks[lChunkPos].push_back(pParticle);
    particles.push_back(pParticle);
}

std::list<std::list<VerletParticle*>*> getChunksInRadius(const glm::vec3& pChunkPos, const glm::vec3& pPos, float pRadius) {
    std::list<std::list<VerletParticle*>*> lRelChunks;
    lRelChunks.push_back(&chunks[pChunkPos]);

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            for (int z = -1; z <= 1; ++z) {
                if (x == 0 && y == 0 && z == 0) {
                    continue;
                }

                const glm::vec3 lNeighbourChunkPos(pChunkPos.x + x, pChunkPos.y + y, pChunkPos.z + z);
                const float lDistToChunk = glm::distance(lNeighbourChunkPos * CHUNK_SIZE, pPos) - CHUNK_SIZE;

                if (lDistToChunk < pRadius && !chunks[lNeighbourChunkPos].empty()) {
                    lRelChunks.push_back(&chunks[lNeighbourChunkPos]);
                }
            }
        }
    }

    for (std::list<VerletParticle*>* lChunk : lRelChunks) {

            std::cout << lChunk->size() << std::endl;

    }
    std::cout << std::endl;

    return lRelChunks;
}