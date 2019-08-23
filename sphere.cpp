#include "sphere.h"

bool Sphere::FindIntersection(std::shared_ptr<Ray> ray) {
    bool intersectionFound = false;

    // Converting the ray from world space to object space
    glm::vec3 objectSpaceRayOrigin = invModelMatrix * glm::vec4(ray->rayOrigin, 1.0f);
    glm::vec3 objectSpaceRayDirection = glm::vec3(invModelMatrix * glm::vec4(ray->rayDirection, 0.0f));

    glm::vec3 oc = objectSpaceRayOrigin - sphereCenter;
    float A = glm::dot(objectSpaceRayDirection, objectSpaceRayDirection);
    float B = 2.0f * glm::dot(oc, objectSpaceRayDirection);
    float C = glm::dot(oc, oc) - sphereRadius * sphereRadius;
    float discriminant = (B * B - 4.0f * A * C);
    if(discriminant < 0) {
        intersectionFound = false;
    } else {
        float t0 = ((-B) - std::sqrt(discriminant)) / (2.0f * A);
        float t1 = ((-B) + std::sqrt(discriminant)) / (2.0f * A);

        if(t0 < 0 && t1 < 0) {
            intersectionFound = false;
        } else if (t0 > 0) {
            ray->intersectionInfo = std::make_shared<Intersect>();
            ray->intersectionInfo->parameterDistance = t0;
            intersectionFound = true;
        } else if (t1 > 0) {
            ray->intersectionInfo = std::make_shared<Intersect>();
            ray->intersectionInfo->parameterDistance = t1;
            intersectionFound = true;
        }
    }

    if(intersectionFound) {
        // Object Space Normal
        glm::vec3 objSpacePOI = Ray::PointAtParameter(objectSpaceRayOrigin, objectSpaceRayDirection, ray->intersectionInfo->parameterDistance);
        glm::vec3 objSpaceNormal = glm::normalize(objSpacePOI - sphereCenter);
        // World Space Normal
        glm::vec3 worldSpaceNormal = glm::normalize(glm::vec3(glm::transpose(invModelMatrix) * glm::vec4(objSpaceNormal, 0.0f)));
        ray->intersectionInfo->worldSpaceIntersectionNormal = worldSpaceNormal;

        // Set the material
        ray->intersectionInfo->material = material;
    }
    return intersectionFound;
}
