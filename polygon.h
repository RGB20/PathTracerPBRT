#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"

struct Triangle {
    std::vector<glm::vec3> pointsOnTriangle;
};

class Polygon : public Shape
{
public:
    Polygon();

    bool FindIntersection(std::shared_ptr<Ray> ray);

    std::vector<Triangle> triangleMesh;
};

#endif // POLYGON_H
