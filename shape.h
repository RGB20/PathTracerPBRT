#ifndef SHAPE_H
#define SHAPE_H
#include <memory>
#include <vector>
#include <iostream>
#include "ray.h"
#include <cmath>
#include "glm/glm.hpp"

class Shape
{
public:
    Shape() {}

    // All intersections are calculated by transforming the ray into the shapes object space
    virtual bool FindIntersection(std::shared_ptr<Ray> ray) = 0;

    virtual ~Shape() {}

    // This matrix takes the object from local object space to world space
    glm::mat4* modelMatrix = nullptr;
    glm::mat4* invModelMatrix = nullptr;
};

#endif // SHAPE_H
