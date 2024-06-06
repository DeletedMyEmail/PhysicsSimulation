#pragma once
#include <vector>

#include "VerletParticle.h"
#include "Window.h"

class Simulation {
public:
    static Simulation* getInstance();

    void run();
    Window& getWindow();
    std::vector<VerletParticle>& getParticles();
private:
    Simulation();
    static void processParticles(const glm::mat4& pViewProj, float pDeltaTime);
private:
    inline static Simulation* sInstance = nullptr;
    static constexpr double METRIC_CALC_INTERVAL = 1.0/20;
    static constexpr double PARTICLE_SPAWN_INTERVAL = 0.05;

    Window mWindow;
    std::vector<VerletParticle> mParticles;
};
