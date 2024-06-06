#include "../include/Simulation.h"
#include "../include/Constants.h"
#include "../include/Metric.h"
#include "../include/Physics.h"
#include "../include/SpatialPartitioning.h"

Simulation::Simulation() : mWindow(Window({1920.0f, 1080.0f, "A Simulation", false, false, true})) {
    mWindow.setWindowFocusCallback([](GLFWwindow* pWindow, const int pEntered) {
        if (pEntered) {
            glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    });
}

Model createConstrainModel(float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);

void Simulation::run() {
    FPSCounter lFPSCounter;
    Model lConstModel = createConstrainModel(CONSTRAIN_RADIUS, VERT_SHADER_PATH, BASIC_FRAG_SHADER, MODEL_PATH);
    const Shader lObjShader(VERT_SHADER_PATH, DIFFUSE_FRAG_SHADER_PATH);

    double lTimeSinceLastSpawn = glfwGetTime();
    double lCurrentTime = 0.0;
    int lObjCount = 0;

    while (mWindow.isRunning()) {
        mWindow.update(lFPSCounter.getLastDeltaTime());

        // metrics
        lFPSCounter.update();
        if (lFPSCounter.getElapsed() >= METRIC_CALC_INTERVAL) {
            std::string lTitle = lFPSCounter.calcToString() + " | Verlet Particles: " + std::to_string(lObjCount);
            glfwSetWindowTitle(mWindow.getGLFWWindow(), lTitle.c_str());
        }

        // spawn new obj ever 0.05s
        lCurrentTime = glfwGetTime();
        if (lCurrentTime - lTimeSinceLastSpawn >= PARTICLE_SPAWN_INTERVAL && lObjCount < MAX_PARTICLE_COUNT) {
            lTimeSinceLastSpawn = lCurrentTime;
            lObjCount++;

            const auto lPos = glm::vec3(rand() % CONSTRAIN_RADIUS - CONSTRAIN_RADIUS/2, 0, rand() % CONSTRAIN_RADIUS - CONSTRAIN_RADIUS/2);
            spawnParticle(createParticle(lPos, PARTICLE_RADIUS,MODEL_PATH, &lObjShader));
        }

        // physics & drawing
        glm::mat4& lViewProj = mWindow.getCamera().getViewPorjection();
        processParticles(lViewProj, static_cast<float>(lFPSCounter.getLastDeltaTime()));
        lConstModel.calModelViewProj(lViewProj);
        lConstModel.draw();
    }

    glfwTerminate();
}

Window& Simulation::getWindow() {
    return mWindow;
}

std::vector<VerletParticle>& Simulation::getParticles() {
    return mParticles;
}

Simulation* Simulation::getInstance() {
    if (sInstance == nullptr) {
        sInstance = new Simulation();
    }

    return sInstance;
}

void Simulation::processParticles(const glm::mat4& pViewProj, const float pDeltaTime) {
    for (VerletParticle* lParticle : particles) {
        if (lParticle == nullptr) continue;

        glm::vec3 lChunkPos = getChunkPos(lParticle->getPosition());
        std::list<std::list<VerletParticle*>*> lRelChunks = getChunksInRadius(lChunkPos, lParticle->getPosition(), PARTICLE_RADIUS);

        applyForces(lParticle);
        handleConstrains(lParticle, glm::vec3(0,0,0), CONSTRAIN_RADIUS);
        handleCollisions(lRelChunks, lParticle);
        updateAndDraw(lParticle, pDeltaTime, pViewProj);
        updateChunk(lParticle, chunks[lChunkPos]);
    }
}

Model createConstrainModel(const float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath) {
    const Shader* lShader = new Shader(pVertexPath, pFragPath);
    const Mesh* lMesh = new Mesh(pModelPath, 0.1f);

    auto lModel = Model(lMesh, lShader);
    lModel.scale(glm::vec3(pRadius));

    return lModel;
}
