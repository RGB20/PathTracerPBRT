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

    virtual bool FindIntersection(std::shared_ptr<Ray> ray) = 0;

    virtual ~Shape() {}

    // This matrix takes the object from local object space to world space
    glm::mat4* modelMatrix = nullptr;
};

#endif // SHAPE_H
