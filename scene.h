#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include <vector>
#include <iostream>
#include "shape.h"
#include "ray.h"
#include "glm/vec3.hpp"
#include "camera.h"

struct Interaction {
    float parameterDistance;
    glm::vec3 worldSpacePointOfIntersection;
    glm::vec3 worldSpaceNormal;

    // We will add materials later to this struct
    std::shared_ptr<Material> material;
};

class Scene
{
public:
    Scene(float screenWidth, float screenHeight);

    void InsertShape(std::shared_ptr<Shape> shape);

    glm::vec3 Color(std::shared_ptr<Ray> ray);
    bool FindIntersectionWithScene(std::shared_ptr<Ray> ray, std::shared_ptr<Interaction> interaction);

    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Shape>> shapes;
};

#endif // SCENE_H
