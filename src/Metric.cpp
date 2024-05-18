#include "../include/Metric.h"

#include <GLFW/glfw3.h>

FPSCounter::FPSCounter() : prevTime(0), currTime(glfwGetTime()), deltaTime(0), elaspedTime(0), fps(0), frameCount(0) {}

void FPSCounter::update() {
    currTime = glfwGetTime();
    deltaTime = currTime - prevTime;
    prevTime = currTime;

    elaspedTime += deltaTime;
    frameCount++;
}

double FPSCounter::calcFPS(double& pAVGFrameTime) {
    fps = 1 / elaspedTime * frameCount;
    pAVGFrameTime = elaspedTime / frameCount * 1000;
    frameCount = 0;
    elaspedTime = 0;
    return fps;

}

std::string FPSCounter::calcToString() {
    double lAvgFrameTime;
    const double lFPS = calcFPS(lAvgFrameTime);
    return "A Simulation | FPS: " + std::to_string(lFPS) + " | AVG Frame Time: " + std::to_string(lAvgFrameTime) + "ms";
}

double FPSCounter::getLastDeltaTime() const {
    return deltaTime;
}

double FPSCounter::getElapsed() const {
    return elaspedTime;
}

double FPSCounter::getFPS() const {
    return fps;
}