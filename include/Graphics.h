#pragma once

#include "PhysicsObj.h"
#include <GLFW/glfw3.h>

#define WIDTH 1600.0f
#define HEIGHT 1000.0f
#define CATCH_MOUSE
#define FULLSCREEN
// TODO: disabling vy sync causes random physics violating energy conservation
#define VYSNC

GLFWwindow* glfwSetup();
PhysicsObj* createObjs(size_t pCount, float pObjRadius, float pSpawnRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);
Model* createConstrainModel(float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);