#include "../libs/glad/glad.h"
#include "../include/Window.h"

#include <iostream>

#include "../include/Input.h"
#include <stdexcept>
#include "../include/Constants.h"

GLFWwindow* glfwSetup(const WindowSetting& pSettings);

Window::Window(const WindowSettings& pSettings) :
    mWindow(glfwSetup(pSettings)),
    mSettings(pSettings),
    mCamera(Camera(90.0f, pSettings.width, pSettings.height, 0.1f, 1000.0f)),
    mLastCursorPos(Input::getMousePosition())
{
    mCamera.translate(glm::vec3(0,CONSTRAIN_RADIUS,-CONSTRAIN_RADIUS*1.5f));
}

void Window::update(const double pDelaTime) {
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
    glClearColor(0.07f, 0.14f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const std::pair<double,double> lCursorPos = Input::getMousePosition();;
    if (lCursorPos.first != mLastCursorPos.first || lCursorPos.second != mLastCursorPos.second)
        mCamera.processCursorMovement(lCursorPos.first - mLastCursorPos.first, lCursorPos.second - mLastCursorPos.second);
    mLastCursorPos = lCursorPos;
    mCamera.processKeyInput(static_cast<float>(pDelaTime));
    mCamera.update();
}

void Window::draw() {}

void Window::setKeyCallback(const GLFWkeyfun pCallbackFun) {
    glfwSetKeyCallback(mWindow, pCallbackFun);
}

void Window::setMouseKeyCallback(const GLFWmousebuttonfun pCallbackFun) {
    glfwSetMouseButtonCallback(mWindow, pCallbackFun);
}

void Window::setCursorPosCallback(const GLFWcursorposfun pCallbackFun) {
    glfwSetCursorPosCallback(mWindow, pCallbackFun);
}

void Window::setWindowFocusCallback(const GLFWcursorenterfun pCallbackFun) {
    glfwSetCursorEnterCallback(mWindow, pCallbackFun);
}

void Window::setCloseCallback(GLFWwindowclosefun pCallbackFun) {
    glfwSetWindowCloseCallback(mWindow, pCallbackFun);
}

bool Window::isRunning() const {
    return glfwWindowShouldClose(mWindow);
}

void Window::stop() {
    glfwSetWindowShouldClose(mWindow, true);
}

WindowSetting Window::getSettings() const {
    return mSettings;
}

GLFWwindow* Window::getGLFWWindow() const {
    return mWindow;
}

Camera& Window::getCamera() {
    return mCamera;
}

GLFWwindow* glfwSetup(const WindowSetting& pSettings) {
    if (!glfwInit()) {
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    if (pSettings.fullscreen) {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        window = glfwCreateWindow(mode->width, mode->height, "A Simulation", glfwGetPrimaryMonitor(), NULL);
    }
    else {
        window = glfwCreateWindow(pSettings.width, pSettings.height, "A Simulation", nullptr, NULL);
    }

    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }


    glfwMakeContextCurrent(window);

    gladLoadGL();
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!pSettings.vysnc) {
        glfwSwapInterval(0);
    }
    if (pSettings.culling) {
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return window;
}
