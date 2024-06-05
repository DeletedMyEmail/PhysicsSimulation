#include "../include/Input.h"
#include <GLFW/glfw3.h>

std::pair<double,double> Input::getMousePosition() {
    double x, y;
    glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
    return {x, y};
}

double Input::getMouseX() {
    return getMousePosition().first;
}

double Input::getMouseY() {
    return getMousePosition().second;
}

bool Input::isKeyPressed(const int pKey) {
    const int lState = glfwGetKey(glfwGetCurrentContext(), pKey);
    return lState == GLFW_PRESS || lState == GLFW_REPEAT;
}

bool Input::isMouseButtonPressed(const int pButton) {
    const int lState = glfwGetMouseButton(glfwGetCurrentContext(), pButton);
    return lState == GLFW_PRESS || lState == GLFW_REPEAT;
}