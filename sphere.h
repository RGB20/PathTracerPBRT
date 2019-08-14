#ifndef SPHERE_H
#define SPHERE_H
#include "shape.h"
#include "ray.h"

class Sphere : public Shape
{
public:
    Sphere() {
        sphereCenter = glm::vec3(0.0f, 0.0f, 0.0f);
        sphereRadius = 1.0f;
    }

    bool FindIntersection(std::shared_ptr<Ray> ray);

    ~Sphere() {}

    // Unity sphere data variables
    glm::vec3 sphereCenter;
    float sphereRadius;
};

#endif // SPHERE_H
