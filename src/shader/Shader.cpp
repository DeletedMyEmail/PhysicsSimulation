#include "../../include/Shader.h"
#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>

class ShaderNotFoundException final : std::exception {};

std::string getShaderSource(const char* pShaderSource) {
    std::ifstream lShaderFile(pShaderSource);

    if (!lShaderFile.is_open())
        throw ShaderNotFoundException();

    std::stringstream lShaderBuffer;
    lShaderBuffer << lShaderFile.rdbuf();

    return lShaderBuffer.str();
}

GLuint createShader(const char* pVertexShaderSource, const char* pFragmentShaderSource) {
    const std::string lVertexString = getShaderSource(pVertexShaderSource);
    const std::string lFragString = getShaderSource(pFragmentShaderSource);

    const char* lVertexCString = lVertexString.c_str();
    const char* lFragCString = lFragString.c_str();

    const GLuint lVertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLuint lFragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(lVertexShader, 1, &lVertexCString, nullptr);
    glShaderSource(lFragShader, 1, &lFragCString, nullptr);

    glCompileShader(lVertexShader);
    glCompileShader(lFragShader);

    GLint success;
    // Überprüfen Sie die Kompilierung des Vertex-Shaders
    glGetShaderiv(lVertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << std::endl;
    }

    // Überprüfen Sie die Kompilierung des Fragment-Shaders
    glGetShaderiv(lFragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
    }

    GLuint lShaderProgram = glCreateProgram();
    glAttachShader(lShaderProgram, lVertexShader);
    glAttachShader(lShaderProgram, lFragShader);

    glDeleteShader(lVertexShader);
    glDeleteShader(lFragShader);

    return lShaderProgram;
}
