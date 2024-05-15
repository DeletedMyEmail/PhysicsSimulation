#include "../../include/Shader.h"
#include <fstream>
#include <sstream>
#include <exception>

class ShaderNotFoundException final : std::exception {};

GLuint createShader(const char* pVertexShaderSource, const char* pFragmentShaderSource) {
    std::ifstream lVertexFile(pVertexShaderSource);
    std::ifstream lFragFile(pFragmentShaderSource);

    if (!lVertexFile.is_open() || !lFragFile.is_open())
        throw ShaderNotFoundException();

    std::stringstream lVertexBuffer, lFragBuffer;;
    lFragBuffer << lFragFile.rdbuf();
    lVertexBuffer << lVertexFile.rdbuf();

    const char* lVertexString = lVertexBuffer.str().c_str();
    const char* lFragString = lFragBuffer.str().c_str();

    GLuint lVertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint lFragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(lVertexShader, 1, &lVertexString, nullptr);
    glShaderSource(lFragShader, 1, &lFragString, nullptr);

    glCompileShader(lVertexShader);
    glCompileShader(lFragShader);

    GLuint lShaderProgram = glCreateProgram();
    glAttachShader(lShaderProgram, lVertexShader);
    glAttachShader(lShaderProgram, lFragShader);

    glDeleteShader(lVertexShader);
    glDeleteShader(lFragShader);

    return lShaderProgram;
}
