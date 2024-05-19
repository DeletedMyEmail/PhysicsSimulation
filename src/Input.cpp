#include "../include/Input.h"

void keyCallback(GLFWwindow* pWindow, int pKey, int pScanCode, int pAction, int pMods) {
    if(pAction == GLFW_PRESS) {
        KEY_STATES[pKey] = true;
    } else if(pAction == GLFW_RELEASE) {
        KEY_STATES[pKey] = false;
    }
}

void mouseKeyCallback(GLFWwindow* pWindow, int pButton, int pAction, int pMods) {}

void cursorPosCallback(GLFWwindow* pWindow, double pX, double pY) {
    currX = pX;
    currY = pY;
    mouseMoved = true;
}

void windowFocusCallback(GLFWwindow* pWindow, int pFocused) {}