#include "scene.h"

Scene::Scene(float screenWidth, float screenHeight) {
    camera = std::make_shared<Camera>(screenWidth, screenHeight);
}

void Scene::InsertShape(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
}

bool Scene::FindIntersectionWithScene(std::shared_ptr<Ray> ray, std::shared_ptr<Interaction> interaction) {
    // Iterate through all the shapes and find an intersection with them.
    float minDistance = FLT_MAX;
    bool intersectionFound = false;
    for (unsigned int shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) {
        // Find the Intersection with the shape mesh
        if (shapes[shapeIndex]->FindIntersection(ray)) {
            intersectionFound = true;
            // Check for the closest mesh that intersects with the ray and return the ray by populating the distance from ray variable
            if (ray->intersectionInfo->parameterDistance > 0 && ray->intersectionInfo->parameterDistance < minDistance) {
                minDistance = ray->intersectionInfo->parameterDistance;

                // Fill the interaction struct
                interaction->parameterDistance = minDistance;
                interaction->worldSpaceNormal = ray->intersectionInfo->worldSpaceIntersectionNormal;
                interaction->pointOfIntersection = Ray::PointAtParameter(ray->rayOrigin, ray->rayDirection, minDistance);
            }
        }
    }
    return intersectionFound;
}

glm::vec3 Scene::Color(std::shared_ptr<Ray> ray) {
    glm::vec3 finalColor{};
    std::shared_ptr<Interaction> interaction = std::make_shared<Interaction>();

    if (FindIntersectionWithScene(ray, interaction)) {
        finalColor = glm::abs(interaction->worldSpaceNormal) * 255.0f;
    }

    return finalColor;
}
