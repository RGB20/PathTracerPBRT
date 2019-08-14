#ifndef RAY_H
#define RAY_H
#include <memory>
#include "glm/vec3.hpp"

struct Intersect {
    float parameterDistance;
    glm::vec3 worldSpaceIntersectionNormal;
};

class Ray
{
public:
    Ray() {}

    Ray(glm::vec3 _rayOrigin, glm::vec3 _rayDirection) : rayOrigin(_rayOrigin), rayDirection(_rayDirection){}

    static glm::vec3 PointAtParameter(glm::vec3 _rayOrigin, glm::vec3 _rayDirection, float distanceOfPointOfIntersection) {
        return _rayOrigin + distanceOfPointOfIntersection * _rayDirection;
    }

    // Ray parameters
    glm::vec3 rayOrigin;
    glm::vec3 rayDirection;
    std::shared_ptr<Intersect> intersectionInfo;
};

#endif // RAY_H
