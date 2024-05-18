#include <iostream>
#include "../include/glad.h"
#include "../include/Shader.h"
#include "../include/Mesh.h"
#include "../include/Metric.h"
#include <GLFW/glfw3.h>

#define WIDTH 1600
#define HEIGHT 1200
#define VYSNC
//#define FULLSCREEN

GLFWwindow* glfwSetup();

int main() {
    GLFWwindow* window = glfwSetup();
    if (!window)
        return -1;

    const Shader lBasicShader("../shader/BasicVert.glsl", "../shader/BasicFrag.glsl");
    const Mesh lMesh("../models/Brunnen.obj");

    FPSCounter lFPSCounter;
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.14f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        lBasicShader.bind();
        lMesh.draw();
        glfwSwapBuffers(window);

        glfwPollEvents();

        lFPSCounter.update();
        if (lFPSCounter.getElapsed() >= 1.0/30) {
            glfwSetWindowTitle(window, lFPSCounter.calcToString().c_str());
        }
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

#ifdef FULLSCREEN
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "A Simulation", glfwGetPrimaryMonitor(), NULL);
#else
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "A Simulation", nullptr, NULL);
#endif


    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    #ifndef VYSNC
        glfwSwapInterval(0);
    #endif

    gladLoadGL();
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0,0,WIDTH,HEIGHT);

    return window;
}