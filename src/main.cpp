#include <iostream>

#include "../libs/glad/glad.h"
#include "../libs/glm/glm.hpp"

#include "../include/Shader.h"
#include "../include/Mesh.h"
#include "../include/Metric.h"
#include "../include/Model.h"
#include "../include/Camera.h"
#include "../include/Input.h"

#include <GLFW/glfw3.h>


#define WIDTH 1800.0f
#define HEIGHT 1200.0f
#define CATCH_MOUSE
//#define VYSNC
//#define FULLSCREEN

#define SPEED 2.0f
GLFWwindow* glfwSetup();

int main() {
    GLFWwindow* window = glfwSetup();
    if (!window)
        return -1;

    const Shader lBasicShader("../shader/BasicVert.glsl", "../shader/BasicFrag.glsl");
    const Mesh lBallMesh("../models/ball.obj");
    const Mesh lCubeMesh("../models/cube.obj", 0.2);

    Model lModels[4];
    for (int i = 0; i < 3; i++) {
        lModels[i] = Model(&lBallMesh, &lBasicShader);
        lModels[i].translate(glm::vec3(i*1.0f, 0.0f, 0.0f));
        lModels[i].scale(glm::vec3(0.2));
    }
    lModels[3] = Model(&lCubeMesh, &lBasicShader);
    lModels[3].scale(glm::vec3(4.0f));

    Camera lCamera(90.0f, WIDTH, HEIGHT, 0.1f, 1000.0f);
    lCamera.translate(glm::vec3(0,-8,0));

    FPSCounter lFPSCounter;

    while(!glfwWindowShouldClose(window)) {
        // metrics
        lFPSCounter.update();
        if (lFPSCounter.getElapsed() >= 1.0/20) {
            glfwSetWindowTitle(window, lFPSCounter.calcToString().c_str());
        }

        // clear
        glClearColor(0.07f, 0.14f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // events
        glfwPollEvents();
        if (mouseMoved) {
            mouseMoved = false;
            lCamera.onMouseMove(currX - lastX, currY - lastY);
            lastX = currX;
            lastY = currY;
        }
        lCamera.onKeyMovement(window, lFPSCounter.getLastDeltaTime());
        lCamera.update();
        // draw
        for (auto & lModel : lModels) {
            lModel.calModelViewProj(lCamera.getViewPorjection());
            lModel.bind();
        }

        glfwSwapBuffers(window);
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

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseKeyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);

#ifdef CATCH_MOUSE
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif

    glfwMakeContextCurrent(window);

#ifndef VYSNC
    glfwSwapInterval(0);
#endif

    gladLoadGL();
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0,0,WIDTH,HEIGHT);

    return window;
}
