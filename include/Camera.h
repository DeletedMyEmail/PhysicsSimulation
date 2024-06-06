#pragma once

#include <string>
#include "../libs/glm/glm.hpp"

class Camera {
public:
    Camera(float pFov, float pWidth, float pHeight, float pNear, float pFar);

    void translate(const glm::vec3& pTranslation);
    void update();
    glm::mat4& getViewPorjection();

    void processCursorMovement(double pRelX, double pRelY);
    void processKeyInput(float pDeltaTime);

    void setSensitive(float pSensitivity);
    float getSensitive() const;

    operator std::string() const;
private:
    void moveFront(float pAmount);
    void moveSideway(float pAmount);
    void moveUp(float pAmount);
private:
    float mSensitivity;
    double mYaw;
    double mPitch;
    float mSpeed;
    glm::vec3 mPosition;

    glm::vec3 mLookAt;
    glm::mat4 mView;
    glm::mat4 mProjection;
    glm::mat4 mViewProjection;
};