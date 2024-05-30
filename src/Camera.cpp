#include "../include/Camera.h"
#include <algorithm>
#include "../include/Input.h"
#include "../libs/glm/ext/matrix_transform.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <sstream>

#include "../libs/glm/gtx/dual_quaternion.hpp"

Camera::Camera(const float pFov, const float pWidth, const float pHeight, const float pNear, const float pFar) :
    projection(glm::perspective(pFov/2.0f, pWidth/pHeight, pNear, pFar)),
    view(glm::mat4(1.0f)),
    yaw(0.0f),
    pitch(0.0f),
    sensitivity(DEFAULT_SENSITIVITY),
    lookAt(glm::vec3(0.0f)),
    position(glm::vec3(0.0f)),
    speed(DEFAULT_SPEED)
{
    update();
}

void Camera::translate(const glm::vec3& pTranslation) {
    view = glm::translate(view, -1.0f*pTranslation);
    position += -1.0f*pTranslation;
}

void Camera::onKeyMovement(GLFWwindow* pWindow, double pDeltaTime) {
    if (KEY_STATES.at(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(pWindow, true);
    if (KEY_STATES.at(GLFW_KEY_W))
        moveFront(pDeltaTime * -speed);
    if (KEY_STATES.at(GLFW_KEY_S))
        moveFront(pDeltaTime * speed);
    if (KEY_STATES.at(GLFW_KEY_A))
        moveSideway(pDeltaTime * speed);
    if (KEY_STATES.at(GLFW_KEY_D))
        moveSideway(pDeltaTime * -speed);
    if (KEY_STATES.at(GLFW_KEY_SPACE))
        moveUp(pDeltaTime * -speed);
    if (KEY_STATES.at(GLFW_KEY_LEFT_SHIFT))
        moveUp(pDeltaTime * speed);
}

void Camera::moveFront(float pAmount) {
    translate(pAmount * lookAt);
}

void Camera::moveSideway(float pAmount) {
    translate(normalize(cross(lookAt, glm::vec3(0.0f, 1.0f, 0.0f))) * pAmount);
}

void Camera::moveUp(float pAmount) {
    translate(pAmount * glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::update() {
    view = glm::lookAt(position, position + lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    viewProjection = projection * view;
}

glm::mat4& Camera::getViewPorjection() {
    return viewProjection;
}

void Camera::onMouseMove(double pRelX, double pRelY) {
    yaw += pRelX * sensitivity;
    pitch -= pRelY * sensitivity;
    pitch = std::clamp(pitch, -89.0, 89.0);

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    lookAt = normalize(front);
}

void Camera::setSensitive(float pSensitivity) {
    sensitivity = pSensitivity;
}

float Camera::getSensitive() const {
    return sensitivity;
}

Camera::operator std::string() const {
    std::ostringstream lStream;
    lStream << "Yaw: " << yaw << " Pitch: " << pitch << " Position: " << position.x << " " << position.y << " " << position.z << " LookAt: " << lookAt.x << " " << lookAt.y << " " << lookAt.z;
    return lStream.str();
}
