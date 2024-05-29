#pragma once

#include <string>
#include <vector>
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "../libs/glm/glm.hpp"

class Mesh {
public:
    Mesh(const char* pFilePath, float pAlpha = 1.0f);
    void draw() const;
private:
    Vertex parseVertex(const char* pLine) const;
    void parseFaceIndices(const std::string& line, std::vector<unsigned int>& pIndices, const std::vector<glm::vec3>& pNormalIndices, std::vector<Vertex>& pVertices);
    bool parse(const char* pModelPath, VertexBuffer& pVertexBuffer, IndexBuffer& pIndexBuffer);
private:
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    float alpha;
};
