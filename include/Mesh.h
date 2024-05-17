#pragma once

#include <string>
#include <vector>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class Mesh {
public:
    explicit Mesh(const char* pFilePath);
    void draw() const;
private:
    static Vertex parseVertex(const char* pLine);
    static void parseFaceIndices(const std::string& line, std::vector<unsigned int>& pIndices);
    static bool parse(const char* pModelPath, VertexBuffer& pVertexBuffer, IndexBuffer& pIndexBuffer);
private:
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
};
