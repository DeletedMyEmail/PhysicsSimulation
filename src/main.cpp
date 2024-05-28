#include <iostream>

#include "../include/Physics.h"
#include "../include/Camera.h"
#include "../include/Graphics.h"
#include "../include/Metric.h"
#include "../include/Input.h"

#define OBJ_COUNT 5
#define OBJ_RADIUS 1.0f
#define CONST_RADIUS 22.0f

int main() {
    GLFWwindow* window = glfwSetup();

    FPSCounter lFPSCounter;
    Camera lCamera(90.0f, WIDTH, HEIGHT, 0.1f, 1000.0f);
    lCamera.translate(glm::vec3(0,CONST_RADIUS,-32));

    PhysicsObj* objs = createObjs(OBJ_COUNT, OBJ_RADIUS, CONST_RADIUS, "../shader/BasicVert.glsl", "../shader/BasicFrag.glsl", "../models/ball.obj");
    Model* lConstModel = createConstrainModel(CONST_RADIUS, "../shader/BasicVert.glsl", "../shader/BasicFrag.glsl", "../models/ball.obj");

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

        // physics & drawing
        if (KEY_STATES[GLFW_KEY_F])
            applyCentralForce(objs, OBJ_COUNT);
        applyForces(objs, OBJ_COUNT);
        handleCollisions(objs,OBJ_COUNT);
        handleConstrains(objs, OBJ_COUNT, glm::vec3(0,0,0), CONST_RADIUS);
        updateAndDraw(objs, OBJ_COUNT, static_cast<float>(lFPSCounter.getLastDeltaTime()), lCamera);

        lConstModel->calModelViewProj(lCamera.getViewPorjection());
        lConstModel->draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
