#include "../include/Metric.h"

#include <GLFW/glfw3.h>

FPSCounter::FPSCounter() : mPrevTime(0), mmCurrTime(glfwGetTime()), mDeltaTime(0), mElaspedTime(0), mFrameCount(0), mFps(0) {}

void FPSCounter::update() {
    mmCurrTime = glfwGetTime();
    mDeltaTime = mmCurrTime - mPrevTime;
    mPrevTime = mmCurrTime;

    mElaspedTime += mDeltaTime;
    mFrameCount++;
}

unsigned int FPSCounter::calcFPS(double& pAVGFrameTime) {
    mFps = 1 / mElaspedTime * mFrameCount;
    pAVGFrameTime = mElaspedTime / mFrameCount * 1000;
    mFrameCount = 0;
    mElaspedTime = 0;
    return mFps;
}

std::string FPSCounter::calcToString() {
    double lAvgFrameTime;
    const unsigned int lFPS = calcFPS(lAvgFrameTime);
    return "A Simulation | FPS: " + std::to_string(lFPS) + " | AVG Frame Time: " + std::to_string(lAvgFrameTime) + "ms";
}

double FPSCounter::getLastDeltaTime() const {
    return mDeltaTime;
}

double FPSCounter::getElapsed() const {
    return mElaspedTime;
}

double FPSCounter::getFPS() const {
    return mFps;
}