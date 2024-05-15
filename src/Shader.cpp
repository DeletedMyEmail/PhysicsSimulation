#include "../include/Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>


Shader::Shader(const char* pVertexShaderSource, const char* pFragmentShaderSource) : mShaderProgram(glCreateProgram()) {
    const std::string lVertexString = parse(pVertexShaderSource);
    const char* lVertexCString = lVertexString.c_str();
    const GLuint lVertShader = compile(lVertexCString, GL_VERTEX_SHADER);

    const std::string lFragString = parse(pFragmentShaderSource);
    const char* lFragCString = lFragString.c_str();
    const GLuint lFragShader = compile(lFragCString, GL_FRAGMENT_SHADER);

    glAttachShader(mShaderProgram, lVertShader);
    glAttachShader(mShaderProgram, lFragShader);

    glLinkProgram(mShaderProgram);

    glDeleteShader(lVertShader);
    glDeleteShader(lFragShader);

    unbind();
}

Shader::~Shader() {
    glDeleteProgram(mShaderProgram);
}

void Shader::bind() const {
    glUseProgram(mShaderProgram);
}

void Shader::unbind() {
    glUseProgram(0);
}

GLuint Shader::compile(const char* pShaderSource, const GLenum pShaderType) {
    const GLuint lShaderID = glCreateShader(pShaderType);

    int lCompRes;
    glShaderSource(lShaderID, 1, &pShaderSource, nullptr);
    glCompileShader(lShaderID);
    glGetShaderiv(lShaderID, GL_COMPILE_STATUS, &lCompRes);

    if(lCompRes != GL_TRUE) {
        int length = 0;
        glGetShaderiv(lShaderID, GL_INFO_LOG_LENGTH, &length);

        char message[length];
        glGetShaderInfoLog(lShaderID, length, &length, message);

        std::cout << "Shader compilation error: " << message << std::endl;
        return 0;
    }

    return lShaderID;
}

std::string Shader::parse(const char* pShaderSource) {
    std::ifstream lShaderFile(pShaderSource);

    if (!lShaderFile.is_open())
        return "";

    std::stringstream lShaderBuffer;
    lShaderBuffer << lShaderFile.rdbuf();

    return lShaderBuffer.str();
}