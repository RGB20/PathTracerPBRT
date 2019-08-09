#include "sphere.h"

bool Sphere::FindIntersection(std::shared_ptr<Ray> ray) {
    bool intersectionFound = false;

    // These are the sphere radius and sphere center in object space which are of unit length
    float sphereRadius = 1.0f;
    glm::vec3 sphereCenter = glm::vec3(0.0f, 0.0f, -50.0f);

    // Converting the ray from world space to object space
    glm::vec3 objectSpaceRayDirection = glm::normalize(glm::inverse(*modelMatrix) * glm::vec4(ray->rayDirection, 0.0f));
    glm::vec3 objectSpaceRayOrigin = glm::inverse(*modelMatrix) * glm::vec4(ray->rayOrigin, 1.0f);

    glm::vec3 oc = ray->rayOrigin - sphereCenter;
    float A = glm::dot(ray->rayDirection, ray->rayDirection);
    float B = 2.0f * glm::dot(oc, ray->rayDirection);
    float C = glm::dot(oc, oc) - sphereRadius * sphereRadius;
    float discriminant = (B * B - 4.0f * A * C);
    if(discriminant < 0) {
        intersectionFound = false;
    } else {
        float t0 = ((-B) - std::sqrt(discriminant)) / (2.0f * A);
        if (t0 > 0) {
            ray->distanceFromRayOrigin = t0;
            intersectionFound = true;
        } else {
            float t1 = ((-B) + std::sqrt(discriminant)) / (2.0f * A);
            if(t1 > 0) {
                ray->distanceFromRayOrigin = t1;
                intersectionFound = true;
            } else {
                intersectionFound = false;
            }
        }
    }

//    if(intersectionFound) {
//        // We will calculte the normal for the point of intersection
//        ray->intersectionNormal = glm::normalize(ray->PointAtParameter() - sphereCenter);
//        ray->intersectionNormal = glm::transpose(glm::inverse(*modelMatrix)) * glm::vec4(ray->intersectionNormal, 0.0f);
//        // We will calculate the point of intersection in world space
//        glm::vec3 pointAtParameterWorldSpace = *modelMatrix * glm::vec4(ray->PointAtParameter(), 1.0f);
//        ray->distanceFromRayOrigin = glm::distance(pointAtParameterWorldSpace, ray->rayOrigin);
//    }
    return intersectionFound;
}
