#include <iostream>
#include "../include/Physics.h"
#include "../include/Camera.h"
#include "../include/Graphics.h"
#include "../include/Metric.h"
#include "../include/Input.h"
#include "../include/SpatialPartitioning.h"

void processParticles(const Camera& lCamera, const FPSCounter& lFPSCounter) {
    for (VerletParticle* lParticle : particles) {
        if (lParticle == nullptr) continue;

        glm::vec3 lChunkPos = getChunkPos(lParticle->getPosition());
        std::list<std::list<VerletParticle*>*> lRelChunks = getChunksInRadius(lChunkPos, lParticle->getPosition(), PARTICLE_RADIUS);

        applyForces(lParticle);
        handleConstrains(lParticle, glm::vec3(0,0,0), CONSTRAIN_RADIUS);
        handleCollisions(lRelChunks, lParticle);
        updateAndDraw(lParticle, static_cast<float>(lFPSCounter.getLastDeltaTime()), lCamera);
        updateChunk(lParticle, chunks[lChunkPos]);
    }
}

int main() {
    GLFWwindow* window = glfwSetup();

    FPSCounter lFPSCounter;
    Camera lCamera(90.0f, WIDTH, HEIGHT, 0.1f, 1000.0f);
    lCamera.translate(glm::vec3(0,CONSTRAIN_RADIUS,-32));

    Model* lConstModel = createConstrainModel(CONSTRAIN_RADIUS, VERT_SHADER_PATH, BASIC_FRAG_SHADER, MODEL_PATH);
    const Shader lObjShader(VERT_SHADER_PATH, DIFFUSE_FRAG_SHADER_PATH);

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
        if (lCurrentTime - lTimeSinceLastSpawn >= 0.05 && lObjCount < MAX_PARTICLE_COUNT) {
            lTimeSinceLastSpawn = lCurrentTime;
            lObjCount++;
            const auto lPos = glm::vec3(rand() % CONSTRAIN_RADIUS - CONSTRAIN_RADIUS/2, 0, rand() % CONSTRAIN_RADIUS - CONSTRAIN_RADIUS/2);
            spawnParticle(createParticle(lPos, PARTICLE_RADIUS,MODEL_PATH, &lObjShader));
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
        processParticles(lCamera, lFPSCounter);
        lConstModel->calModelViewProj(lCamera.getViewPorjection());
        lConstModel->draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}