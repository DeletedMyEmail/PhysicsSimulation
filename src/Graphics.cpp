#include "../include/Graphics.h"
#include "../include/Input.h"
#include <iostream>

GLFWwindow* glfwSetup() {
    if (!glfwInit()) {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
#ifdef FULLSCREEN
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(mode->width, mode->height, "A Simulation", glfwGetPrimaryMonitor(), NULL);

    #else
    window = glfwCreateWindow(WIDTH, HEIGHT, "A Simulation", nullptr, NULL);
#endif

    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseKeyCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);

#ifdef CATCH_MOUSE
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif

    glfwMakeContextCurrent(window);

#ifndef VYSNC
    glfwSwapInterval(0);
#endif

    gladLoadGL();
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}

Model* createConstrainModel(const float pRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath) {
    const Shader lShader(pVertexPath, pFragPath);
    const auto lMesh = new Mesh(pModelPath, 0.1f);

    const auto lModel = new Model(lMesh, &lShader);
    lModel->scale(glm::vec3(pRadius));

    return lModel;
}

PhysicsObj* createObjs(const size_t pCount, const float pObjRadius, const float pSpawnRadius, const char* pVertexPath, const char* pFragPath, const char* pModelPath) {
    const Shader* lShader = new Shader(pVertexPath, pFragPath);
    const auto objs = new PhysicsObj[pCount];

    srand(time(nullptr));
    for (int i = 0; i < pCount; i++) {
        const auto lMesh = new Mesh(pModelPath);
        const auto lModel =  new Model(lMesh, lShader);
        lModel->scale(glm::vec3(pObjRadius));

        auto lPos = glm::vec3(rand(), rand(), rand());
        lPos = glm::normalize(lPos) * (0.0f + rand() % static_cast<int>(pSpawnRadius - pObjRadius));

        objs[i] = *new PhysicsObj(lModel, lPos, pObjRadius);
    }

    return objs;
}

PhysicsObj* createObj(glm::vec3 pPos, float pObjRadius, const char* pModelPath, const Shader* lShader) {
    const auto lMesh = new Mesh(pModelPath);
    const auto lModel =  new Model(lMesh, lShader);
    lModel->scale(glm::vec3(pObjRadius));

    return new PhysicsObj(lModel, pPos, pObjRadius);
}
