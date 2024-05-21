#include <iostream>

#include "../libs/glad/glad.h"
#include "../libs/glm/glm.hpp"

#include "../include/Shader.h"
#include "../include/Mesh.h"
#include "../include/Metric.h"
#include "../include/Model.h"
#include "../include/Camera.h"
#include "../include/Input.h"
#include "../include/PhysicsObj.h"

#include <GLFW/glfw3.h>


#define WIDTH 1800.0f
#define HEIGHT 1200.0f
#define CATCH_MOUSE
//#define VYSNC
//#define FULLSCREEN

#define OBJ_COUNT 3
#define OBJ_RADIUS 1.0f
#define CONST_RADIUS 22.0f
#define G -9.8f

GLFWwindow* glfwSetup();

void applyForces(PhysicsObj pObj[], int pSize) {
    for (int i = 0; i < pSize; i++) {
        pObj[i].applyForce(glm::vec3(0,G,0));
    }
}

void updatePositions(PhysicsObj pObj[], int pSize, float pDeltaTime, Camera pCam) {
    for (int i = 0; i < pSize; i++) {
        pObj[i].updatePos(pDeltaTime);
        pObj[i].getModel()->calModelViewProj(pCam.getViewPorjection());
        pObj[i].getModel()->draw();
    }
}

void handleConstrains(PhysicsObj pObjs[], int pSize, glm::vec3 pConstCenter, float pConstRadius) {
    for (int i = 0; i < pSize; i++) {
        glm::vec3 lToContiner = pConstCenter - pObjs[i].getPosition();
        float lDist = glm::length(lToContiner);
        if ((lDist + pObjs[i].getRadius()) > pConstRadius) {
            glm::vec3 lNorm = lToContiner / lDist;
            pObjs[i].getPosition() = pConstCenter - lNorm * (pConstRadius - pObjs[i].getRadius());
        }
    }
}

void handleCollisions(PhysicsObj pObj[], int pSize) {
    for (int i = 0; i < pSize; i++) {
        for (int j = 0; j < pSize; j++) {
            pObj[i].collide(pObj[j]);
        }
    }
}

int main() {
    GLFWwindow* window = glfwSetup();
    if (!window)
        return -1;

    FPSCounter lFPSCounter;
    Camera lCamera(90.0f, WIDTH, HEIGHT, 0.1f, 1000.0f);

    const Shader lBasicShader("../shader/BasicVert.glsl", "../shader/BasicFrag.glsl");

    Mesh* lBallMesh = new Mesh("../models/ball.obj", 0.05f);
    Model* lContainerModel =  new Model(lBallMesh, &lBasicShader);
    lContainerModel->scale(glm::vec3(CONST_RADIUS));

    PhysicsObj objs[OBJ_COUNT];
    for (int i = 0; i < OBJ_COUNT; i++) {
        Mesh* lMesh = new Mesh("../models/ball.obj");
        Model* lModel =  new Model(lMesh, &lBasicShader);
        //lModel->scale(glm::vec3(1));
        objs[i] = PhysicsObj(lModel, glm::vec3(0.0f), 1.0f);
        glm::vec3 lRanPos = glm::vec3(rand() % 8, rand() % 8, rand() % 8);
        objs[i].move(lRanPos);
    }

    lCamera.pitch = -16;
    lCamera.yaw = -86;
    lCamera.position = glm::vec3(-0.7f, 0.6f, -35.0f);
    lCamera.lookAt = glm::vec3(0.06f, -0.28f, 0.95f);

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

        applyForces(objs, OBJ_COUNT);
        handleConstrains(objs, OBJ_COUNT, glm::vec3(0,0,0), CONST_RADIUS);
        handleCollisions(objs,OBJ_COUNT);
        updatePositions(objs, OBJ_COUNT, lFPSCounter.getLastDeltaTime(), lCamera);

        lContainerModel->calModelViewProj(lCamera.getViewPorjection());
        lContainerModel->draw();

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

    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0,0,WIDTH,HEIGHT);

    return window;
}
