#include "../include/Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

Mesh::Mesh(const char* pFilePath, float pAlpha) : vertexBuffer(VertexBuffer()), indexBuffer(IndexBuffer()), alpha(pAlpha) {
    if (!parse(pFilePath, vertexBuffer, indexBuffer)) {
        throw std::runtime_error("Could not parse model file.");
    }
}

void Mesh::draw() const {
    vertexBuffer.bind();
    indexBuffer.bind();
    glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

Vertex Mesh::parseVertex(const char* pLine) const {
    Vertex lVertex{0,0,0,1,0.5,0.2,alpha};
    sscanf(pLine, "v %f %f %f", &lVertex.x, &lVertex.y, &lVertex.z);
    return lVertex;
}

void Mesh::parseFaceIndices(const std::string& line, std::vector<unsigned int>& pIndices) {
    std::istringstream iss(line);
    std::string token;

    // ignore command character ("f ")
    std::getline(iss, token, ' ');

    for (int i = 0; i < 3; i++) {
        std::getline(iss, token, ' ');
        if (token.find('/') != std::string::npos) {
            std::istringstream indexStream(token);
            std::getline(indexStream, token, '/');
        }

        pIndices.push_back(std::stoul(token)-1);
    }
}

bool Mesh::parse(const char* pModelPath, VertexBuffer& pVertexBuffer, IndexBuffer& pIndexBuffer) {
    std::ifstream lFile(pModelPath);
    if (!lFile) {
        std::cerr << "Die Datei konnte nicht geöffnet werden.\n";
        return false;
    }

    std::vector<Vertex> lVertices;
    std::vector<unsigned int> lIndices;

    std::string lLine;
    while (std::getline(lFile, lLine)) {
        if (lLine[0] == 'v') {
            lVertices.push_back(parseVertex(lLine.c_str()));
        } else if (lLine[0] == 'f') {
            parseFaceIndices(lLine, lIndices);
        }
    }

    lFile.close();

    auto* lVerticesArray = new Vertex[lVertices.size()];
    auto* lIndicesArray = new unsigned int[lIndices.size()];

    std::copy(lVertices.begin(), lVertices.end(), lVerticesArray);
    std::copy(lIndices.begin(), lIndices.end(), lIndicesArray);

    // TODO: delete lVerticesArray and lIndicesArray - idk why it crashed when using stack memory
    pVertexBuffer = *new VertexBuffer(lVerticesArray, lVertices.size());
    pIndexBuffer =  *new IndexBuffer(lIndicesArray, lIndices.size());

    return true;
}