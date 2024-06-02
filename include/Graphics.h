#pragma once

#include "VerletParticle.h"
#include <GLFW/glfw3.h>

GLFWwindow* glfwSetup();
Model* createConstrainModel(float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);