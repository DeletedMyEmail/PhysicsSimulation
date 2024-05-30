#pragma once

#include "VerletParticle.h"
#include <GLFW/glfw3.h>

#define WIDTH 1200.0f
#define HEIGHT 1000.0f
#define CATCH_MOUSE
//#define FULLSCREEN
// TODO: disabling vy sync causes random physics violating energy conservation
#define VYSNC
//#define CULLING

GLFWwindow* glfwSetup();
Model* createConstrainModel(float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);