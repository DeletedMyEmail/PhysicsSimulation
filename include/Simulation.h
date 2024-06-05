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
    void processParticles(const glm::mat4& pViewProj, float pDeltaTime);
private:
    inline static Simulation* sInstance = nullptr;

    Window mWindow;
    std::vector<VerletParticle> mParticles;
};
