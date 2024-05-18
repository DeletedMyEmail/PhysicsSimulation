#pragma once
#include <string>

class FPSCounter {
public:
    FPSCounter();

    /*! @brief Updates counters and calculates delta time - should be called once per frame
     */
    void update();

    /*! @brief Calculates fps and average frame time and resets all counters
     *
     *  @param pAVGFrameTime reference to a double to store the average frame time
     *  @return the calculated fps
     */
    double calcFPS(double& pAVGFrameTime);

    /*! @brief Calculates fps and average frame time and resets all counters
     *
     *  @return The string representation of the fps and average frame time
     */
    std::string calcToString();

    double getFPS() const;
    double getElapsed() const;
    double getLastDeltaTime() const;
private:
    double prevTime, currTime, deltaTime, elaspedTime, fps;
    unsigned int frameCount;
};
