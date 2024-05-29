#pragma once

#include "VerletObj.h"
#include <GLFW/glfw3.h>

#define WIDTH 1600.0f
#define HEIGHT 1000.0f
#define CATCH_MOUSE
//#define FULLSCREEN
// TODO: disabling vy sync causes random physics violating energy conservation
#define VYSNC
//#define CULLING

GLFWwindow* glfwSetup();
PhysicsObj* createObjs(size_t pCount, float pObjRadius, float pSpawnRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);
PhysicsObj* createObj(glm::vec3 pPos, float pObjRadius, const char* pModelPath, const Shader* lShader);
Model* createConstrainModel(float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath);