#include "../include/Camera.h"
#include <algorithm>
#include "../libs/glm/ext/matrix_transform.hpp"
#include "../libs/glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <sstream>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include "../include/Input.h"
#include "../libs/glm/gtx/dual_quaternion.hpp"

Camera::Camera(const float pFov, const float pWidth, const float pHeight, const float pNear, const float pFar) :
    mProjection(glm::perspective(pFov/2.0f, pWidth/pHeight, pNear, pFar)),
    mView(glm::mat4(1.0f)),
    mYaw(0.0f),
    mPitch(0.0f),
    mSensitivity(0.2f),
    mLookAt(glm::vec3(0.0f)),
    mPosition(glm::vec3(0.0f)),
    mSpeed(6.5f)
{
    update();
}

void Camera::translate(const glm::vec3& pTranslation) {
    mView = glm::translate(mView, -1.0f*pTranslation);
    mPosition += -1.0f*pTranslation;
}

void Camera::processKeyInput(const float pDeltaTime) {
    if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
        // TODO: stop window
        return;
    if (Input::isKeyPressed(GLFW_KEY_W))
        moveFront(pDeltaTime * -mSpeed);
    if (Input::isKeyPressed(GLFW_KEY_S))
        moveFront(pDeltaTime * mSpeed);
    if (Input::isKeyPressed(GLFW_KEY_A))
        moveSideway(pDeltaTime * mSpeed);
    if (Input::isKeyPressed(GLFW_KEY_D))
        moveSideway(pDeltaTime * -mSpeed);
    if (Input::isKeyPressed(GLFW_KEY_SPACE))
        moveUp(pDeltaTime * -mSpeed);
    if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        moveUp(pDeltaTime * mSpeed);
}

void Camera::moveFront(float pAmount) {
    translate(pAmount * mLookAt);
}

void Camera::moveSideway(float pAmount) {
    translate(normalize(cross(mLookAt, glm::vec3(0.0f, 1.0f, 0.0f))) * pAmount);
}

void Camera::moveUp(float pAmount) {
    translate(pAmount * glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::update() {
    mView = glm::lookAt(mPosition, mPosition + mLookAt, glm::vec3(0.0f, 1.0f, 0.0f));
    mViewProjection = mProjection * mView;
}

glm::mat4& Camera::getViewPorjection() {
    return mViewProjection;
}

void Camera::processCursorMovement(double pRelX, double pRelY) {
    mYaw += pRelX * mSensitivity;
    mPitch -= pRelY * mSensitivity;
    mPitch = std::clamp(mPitch, -89.0, 89.0);

    glm::vec3 front;
    front.x = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
    front.y = sin(glm::radians(mPitch));
    front.z = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
    mLookAt = normalize(front);
}

void Camera::setSensitive(float pSensitivity) {
    mSensitivity = pSensitivity;
}

float Camera::getSensitive() const {
    return mSensitivity;
}

Camera::operator std::string() const {
    std::ostringstream lStream;
    lStream << "Yaw: " << mYaw << " Pitch: " << mPitch << " Position: " << mPosition.x << " " << mPosition.y << " " << mPosition.z << " LookAt: " << mLookAt.x << " " << mLookAt.y << " " << mLookAt.z;
    return lStream.str();
}
