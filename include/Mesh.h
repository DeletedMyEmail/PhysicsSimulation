#pragma once

#include <string>
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class Mesh {
public:
    explicit Mesh(const char* pFilePath, float pAlpha = 1.0f);
    ~Mesh();

    void draw() const;
private:
    Vertex parseVertex(const char* pLine) const;
    void parseFaceIndices(const std::string& line, std::vector<unsigned int>& pIndices);
    bool parse(const char* pModelPath, VertexBuffer& pVertexBuffer, IndexBuffer& pIndexBuffer);
private:
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    float alpha;
};
