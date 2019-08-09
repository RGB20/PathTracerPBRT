#ifndef RAY_H
#define RAY_H
#include "glm/vec3.hpp"

class Ray
{
public:
    Ray() {}

    Ray(glm::vec3 _rayOrigin, glm::vec3 _rayDirection) : rayOrigin(_rayOrigin), rayDirection(_rayDirection){}

    glm::vec3 PointAtParameter() const {
        return rayOrigin + distanceFromRayOrigin * rayDirection;
    }

    glm::vec3 rayOrigin;
    glm::vec3 rayDirection;
    float distanceFromRayOrigin;
    glm::vec3 intersectionNormal;
};

#endif // RAY_H
