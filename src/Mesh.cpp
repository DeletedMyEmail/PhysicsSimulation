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
    Vertex lVertex{0,0,0,0.0,0.0,0.0,0.51,0.5,0.5,alpha};

    sscanf(pLine, "v %f %f %f", &lVertex.x, &lVertex.y, &lVertex.z);
    return lVertex;
}

void Mesh::parseFaceIndices(const std::string& line, std::vector<unsigned int>& pIndices, const std::vector<glm::vec3>& pNormalIndices, std::vector<Vertex>& pVertices) {
    std::istringstream iss(line);
    std::string token;

    // ignore command character ("f ")
    std::getline(iss, token, ' ');

    for (int i = 0; i < 3; i++) {
        std::getline(iss, token, ' ');
        // vt and vn are given
        if (token.find('/') != std::string::npos) {
            // read v
            std::string lVToken = token.substr(0, token.find('/'));
            unsigned long lVIndex = std::stoul(lVToken)-1;
            // ignore vt
            token = token.substr(token.find('/')+1);
            // read normal
            std::string lNToken = token.substr(token.find('/')+1);
            unsigned long lNIndex = std::stoul(lNToken)-1;

            pIndices.push_back(lVIndex);
            pVertices[lVIndex].nx = pNormalIndices[lNIndex].x;
            pVertices[lVIndex].ny = pNormalIndices[lNIndex].y;
            pVertices[lVIndex].nz = pNormalIndices[lNIndex].z;
        }
        else {
            pIndices.push_back(std::stoul(token)-1);
        }
    }
}

glm::vec3 parseNormal(const char* pLine) {
    glm::vec3 lNormal;
    sscanf(pLine, "vn %f %f %f", &lNormal.x, &lNormal.y, &lNormal.z);
    return lNormal;
}

bool Mesh::parse(const char* pModelPath, VertexBuffer& pVertexBuffer, IndexBuffer& pIndexBuffer) {
    std::ifstream lFile(pModelPath);
    if (!lFile) {
        std::cerr << "Die Datei konnte nicht geöffnet werden.\n";
        return false;
    }

    std::vector<Vertex> lVertices;
    std::vector<unsigned int> lIndices;
    std::vector<glm::vec3> lNormals;
    unsigned int lVNormalCounter = 0;

    std::string lLine;
    while (std::getline(lFile, lLine)) {
        // TODO: bounds checking
        if (lLine.substr(0, 2) == "v ")
            lVertices.push_back(parseVertex(lLine.c_str()));
        else if (lLine.substr(0, 2) == "vn")
            lNormals.push_back(parseNormal(lLine.c_str()));
        else if (lLine.substr(0, 2) == "f ")
            parseFaceIndices(lLine, lIndices, lNormals, lVertices);
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