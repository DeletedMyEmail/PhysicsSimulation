#pragma once
#include "../libs/glm/vec3.hpp"

class VerletObj {
public:
    VerletObj(const glm::vec3& pPosition, float pRadius);
    void update(float pDeltaTime);
    void applyForce(const glm::vec3& pForce);

    void setPosition(const glm::vec3& pPosition);
    glm::vec3& getPosition();
    float getRadius();
private:
    glm::vec3 position;
    glm::vec3 prePosition;
    glm::vec3 acceleration;
    float radius;
};
