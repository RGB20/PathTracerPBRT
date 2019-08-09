#include "scene.h"

Scene::Scene(float screenWidth, float screenHeight) {
    camera = std::make_shared<Camera>(screenWidth, screenHeight);
}

void Scene::InsertShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}

glm::vec3 Scene::Color(std::shared_ptr<Ray> ray) {
    glm::vec3 finalColor{};

    float minDistance = FLT_MAX;
    bool intersectionFound = false;
    // Iterate through all the shapes and find an intersection with them.
    for (unsigned int shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) {
        ray->distanceFromRayOrigin = FLT_MAX;
        // Find the Intersection with the shape mesh
        intersectionFound = shapes[shapeIndex]->FindIntersection(ray);
        if (intersectionFound) {
            // Check for the closest mesh that intersects with the ray and return the ray by populating the distance from ray variable
            if (ray->distanceFromRayOrigin > 0 && ray->distanceFromRayOrigin < minDistance) {
                minDistance = ray->distanceFromRayOrigin;
                finalColor = glm::vec3(0,0,255);//ray->intersectionNormal;
            }
        }
    }

    return finalColor;
}
