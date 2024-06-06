#pragma once

#include <unordered_map>
#include <GLFW/glfw3.h>
#include "Camera.h"

typedef struct WindowSetting {
    float width;
    float height;
    const char* title;
    bool fullscreen;
    bool culling;
    bool vysnc;
} WindowSettings;

class Window {
public:
    explicit Window(const WindowSettings& pSettings);
    void update(double pDelaTime);
    void draw();

    void setKeyCallback(GLFWkeyfun pCallbackFun);
    void setMouseKeyCallback(GLFWmousebuttonfun pCallbackFun);
    void setCursorPosCallback(GLFWcursorposfun pCallbackFun);
    void setWindowFocusCallback(GLFWcursorenterfun pCallbackFun);
    void setCloseCallback(GLFWwindowclosefun pCallbackFun);

    bool isRunning() const;
    void stop();
    WindowSetting getSettings() const;
    GLFWwindow* getGLFWWindow() const;
    Camera& getCamera();
private:
    GLFWwindow* mWindow;
    WindowSetting mSettings;
    Camera mCamera;
    std::pair<double, double> mLastCursorPos;
};