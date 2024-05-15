#include <iostream>
#include <valarray>
#include "../include/glad.h"
#include "../include/Shader.h"
#include "../include/Model.h"
#include <GLFW/glfw3.h>

#include "../include/IndexBuffer.h"
#include "../include/VertexBuffer.h"

#define WIDTH 1200
#define HEIGHT 800

GLFWwindow* glfwSetup();

int main() {
    GLFWwindow* window = glfwSetup();
    if (!window)
        return -1;

    Vertex lVertices[] = {
        Vertex{
            -0.5f, -0.5f, 0.0f,
            0.9f, 0.2f, 0.5f
        },
        Vertex{
            0.0f, 0.5f, 0.0f,
            0.1f, 0.8f, 0.2f
        },
        Vertex{
            0.5f, 0.5f, 0.0f,
            0.4f, 0.5f, 0.1f
        },
    };
    unsigned int lIndices[] = {
        0, 1, 2
    };

    const Shader lBasicShader("../shader/BasicVert.glsl", "../shader/BasicFrag.glsl");

    const VertexBuffer lVertBuffer(lVertices, 3);
    const IndexBuffer lIndexBuffer(lIndices, 3);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.14f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        lBasicShader.bind();
        lVertBuffer.bind();
        lIndexBuffer.bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* glfwSetup() {
    if (!glfwInit()) {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "A Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0,0,WIDTH,HEIGHT);

    return window;
}