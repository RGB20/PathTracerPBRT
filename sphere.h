#ifndef SPHERE_H
#define SPHERE_H
#include "shape.h"
#include "ray.h"

class Sphere : public Shape
{
public:
    Sphere() {}

    bool FindIntersection(std::shared_ptr<Ray> ray);

    ~Sphere() {}
};

#endif // SPHERE_H
