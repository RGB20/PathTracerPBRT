#ifndef SHAPE_H
#define SHAPE_H
#include <memory>
#include <vector>
#include <iostream>
#include "ray.h"
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shape
{
public:
    Shape() {}

    // All intersections are calculated by transforming the ray into the shapes object space
    virtual bool FindIntersection(std::shared_ptr<Ray> ray) = 0;

    virtual ~Shape() {}

    // This matrix takes the object from local object space to world space
    glm::mat4* modelMatrix;
    glm::mat4* invModelMatrix;
};

#endif // SHAPE_H
