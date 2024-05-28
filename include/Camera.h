#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include "../libs/glm/glm.hpp"

#define DEFAULT_SPEED 6.5f
#define DEFAULT_SENSITIVITY 0.20f

class Camera {
public:
    Camera(float pFov, float pWidth, float pHeight, float pNear, float pFar);

    void translate(const glm::vec3& pTranslation);
    void update();
    glm::mat4& getViewPorjection();

    void onMouseMove(double pRelX, double pRelY);
    void onKeyMovement(GLFWwindow* pWindow, double pDeltaTime);

    void setSensitive(float pSensitivity);
    float getSensitive() const;

    operator std::string() const;
private:
    void moveFront(float pAmount);
    void moveSideway(float pAmount);
    void moveUp(float pAmount);
public:
    float sensitivity;
    double yaw;
    double pitch;
    glm::vec3 lookAt;
    glm::vec3 position;
    float speed;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;
};