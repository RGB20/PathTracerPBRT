#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"

class Polygon : public Shape
{
public:
    Polygon(std::vector<glm::vec3> _meshPoints, std::vector<int> _triangulatedMeshIndixes, bool backfaceCullingStatus, bool _clockwiseTriangulation) {
        for (unsigned int meshPointIndixes = 0; meshPointIndixes < _meshPoints.size(); meshPointIndixes++) {
            meshPoints.push_back(_meshPoints[meshPointIndixes]);
        }

        for (unsigned int triangleArrayIndixes = 0; triangleArrayIndixes < _triangulatedMeshIndixes.size(); triangleArrayIndixes++) {
            triangulatedMeshIndixes.push_back(_triangulatedMeshIndixes[triangleArrayIndixes]);
        }

        backfaceCulling = backfaceCullingStatus;
        clockwiseTriangulation = _clockwiseTriangulation;
    }

    bool FindIntersection(std::shared_ptr<Ray> ray);

    std::vector<glm::vec3> meshPoints;
    std::vector<int> triangulatedMeshIndixes;
    bool backfaceCulling;
    bool clockwiseTriangulation;
};

#endif // POLYGON_H
