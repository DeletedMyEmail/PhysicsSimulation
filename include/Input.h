#pragma once
#include <utility>

class Input {
public:
    static std::pair<double,double> getMousePosition();
    static double getMouseX();
    static double getMouseY();
    static bool isKeyPressed(int pKey);
    static bool isMouseButtonPressed(int pButton);
};
