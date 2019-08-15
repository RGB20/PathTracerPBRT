#ifndef PLANE_H
#define PLANE_H
#include "shape.h"

class Plane : public Shape
{
public:
    Plane() {
        // NOTE: The plane in object space is on the XY axis and facing the camera
        pointOnPlane = glm::vec3(0.0f, 0.0f, 0.0f);
        // normal in object space
        normal = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    bool FindIntersection(std::shared_ptr<Ray> ray);
    glm::vec3 pointOnPlane;
    glm::vec3 normal;
};

#endif // PLANE_H
