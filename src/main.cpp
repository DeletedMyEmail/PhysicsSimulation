#include <iostream>
#include <valarray>
#include "../include/glad.h"
#include "../include/Shader.h"
#include "../include/Model.h"
#include <GLFW/glfw3.h>

#define WIDTH 1200
#define HEIGHT 800

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "A Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0,0,WIDTH,HEIGHT);

    const Shader lBasicShader("/home/joshua/CLionProjects/SimulationGoesBRr/shader/BasicVert.glsl", "/home/joshua/CLionProjects/SimulationGoesBRr/shader/BasicFrag.glsl");

    constexpr Vertex lVertices[] = {
        Vertex{
            -0.9f, -0.5f, 0.0f,
            0.9f, 0.5f, 0.0f,
        },
        Vertex{
            -0.45f, 0.5f, 0.0f,
            0.9f, 0.5f, 0.0f,
        },
        Vertex{
            0.0f, -0.5f, 0.0f,
            0.9f, 0.5f, 0.0f,
        },
    };

    // create Vertex Array Object and Vertex Buffer Object
    GLuint lVBO, lVAO, lEBO;
    glGenVertexArrays(1, &lVAO);
    glGenBuffers(1, &lVBO);
    //glGenBuffers(1, &lEBO);

    glBindVertexArray(lVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lVertices), lVertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // specify position attribute for the shader
    // stride is offset between consecutive vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, r)));
    glEnableVertexAttribArray(1);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.14f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        lBasicShader.bind();
        glBindVertexArray(lVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &lVAO);
    glDeleteBuffers(1, &lVBO);
    glDeleteBuffers(1, &lEBO);
    glfwTerminate();
    return 0;
}