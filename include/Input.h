#pragma once

#include <unordered_map>

#include "Camera.h"
#include "GLFW/glfw3.h"

inline std::unordered_map<int, bool> KEY_STATES = {
    {GLFW_KEY_W, false},
    {GLFW_KEY_A, false},
    {GLFW_KEY_S, false},
    {GLFW_KEY_D, false},
    {GLFW_KEY_SPACE, false},
    {GLFW_KEY_LEFT_SHIFT, false},
    {GLFW_KEY_F, false},
    {GLFW_KEY_ESCAPE, false}
};

inline bool mouseMoved = false;
inline double lastX = 0.0, lastY = 0.0, currX = 0.0, currY = 0.0;

void keyCallback(GLFWwindow* pWindow, int pKey, int pScanCode, int pAction, int pMods);

void mouseKeyCallback(GLFWwindow* pWindow, int pButton, int pAction, int pMods);

void cursorPosCallback(GLFWwindow* pWindow, double pX, double pY);

void windowFocusCallback(GLFWwindow* pWindow, int pFocused);