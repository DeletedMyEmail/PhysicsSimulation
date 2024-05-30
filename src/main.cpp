#include <forward_list>
#include "../include/Physics.h"
#include "../include/Camera.h"
#include "../include/Graphics.h"
#include "../include/Metric.h"
#include "../include/Input.h"

#define MAX_OBJ_COUNT 400
#define OBJ_RADIUS 1.0f
#define CONST_RADIUS 22
#define VERT_SHADER_PATH "../shader/BasicVert.glsl"
#define DIFFUSE_FRAG_SHADER_PATH "../shader/DiffuseFrag.glsl"
#define BASIC_FRAG_SHADER "../shader/BasicFrag.glsl"
#define MODEL_PATH "../models/sphere.obj"

int main() {
    GLFWwindow* window = glfwSetup();

    FPSCounter lFPSCounter;
    Camera lCamera(90.0f, WIDTH, HEIGHT, 0.1f, 1000.0f);
    lCamera.translate(glm::vec3(0,CONST_RADIUS,-32));

    Model* lConstModel = createConstrainModel(CONST_RADIUS, VERT_SHADER_PATH, BASIC_FRAG_SHADER, MODEL_PATH);
    std::forward_list<VerletParticle*> lObjs;
    Shader lObjShader(VERT_SHADER_PATH, DIFFUSE_FRAG_SHADER_PATH);

    double lTimeSinceLastSpawn = glfwGetTime();
    double lCurrentTime = 0.0;
    int lObjCount = 0;

    while(!glfwWindowShouldClose(window)) {
        // metrics
        lFPSCounter.update();
        if (lFPSCounter.getElapsed() >= 1.0/20) {
            std::string lTitle = lFPSCounter.calcToString() + " | Verlet Particles: " + std::to_string(lObjCount);
            glfwSetWindowTitle(window, lTitle.c_str());
        }

        // spawn new obj ever 0.05s
        lCurrentTime = glfwGetTime();
        if (lCurrentTime - lTimeSinceLastSpawn >= 0.05 && lObjCount < MAX_OBJ_COUNT) {
            lTimeSinceLastSpawn = lCurrentTime;
            lObjCount++;
            glm::vec3 lPos = glm::vec3(rand() % CONST_RADIUS - CONST_RADIUS/2, 0, rand() % CONST_RADIUS - CONST_RADIUS/2);
            lObjs.push_front(createObj(lPos, OBJ_RADIUS,MODEL_PATH, &lObjShader));
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
            applyCentralForce(lObjs);
        applyForces(lObjs);
        handleCollisions(lObjs);
        handleConstrains(lObjs, glm::vec3(0,0,0), CONST_RADIUS);
        updateAndDraw(lObjs, static_cast<float>(lFPSCounter.getLastDeltaTime()), lCamera);

        lConstModel->calModelViewProj(lCamera.getViewPorjection());
        lConstModel->draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
