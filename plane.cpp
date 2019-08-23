#include "plane.h"

bool Plane::FindIntersection(std::shared_ptr<Ray> ray) {
    bool intersectionFound = false;
    float parameterDistance;

    // Converting ray to object space
    glm::vec3 objectSpaceRayOrigin = invModelMatrix * glm::vec4(ray->rayOrigin, 1.0f);
    glm::vec3 objectSpaceRayDirection = glm::vec3(invModelMatrix * glm::vec4(ray->rayDirection, 0.0f));

    float denominator = glm::dot(normal, objectSpaceRayDirection);
    if (std::fabs(denominator) > 0.0001f) {
        glm::vec3 difference = pointOnPlane - objectSpaceRayOrigin;
        parameterDistance = glm::dot(difference, normal) / denominator;
        if (parameterDistance > 0.0001f) {
            // Check if the point is inside the plane
            glm::vec3 objectSpacePOI = Ray::PointAtParameter(objectSpaceRayOrigin, objectSpaceRayDirection, parameterDistance);
            if(objectSpacePOI.x >= -1.0f && objectSpacePOI.x <= 1.0f &&
                    objectSpacePOI.y >= -1.0f && objectSpacePOI.y <= 1.0f &&
                    objectSpacePOI.z >= -0.0001f && objectSpacePOI.z <= 0.0001f) {
                // Initialize and set the parameter distance
                ray->intersectionInfo = std::make_shared<Intersect>();
                ray->intersectionInfo->parameterDistance = parameterDistance;

                // We will calculate the world space normal
                ray->intersectionInfo->worldSpaceIntersectionNormal = glm::normalize(glm::vec3(glm::transpose(invModelMatrix) * glm::vec4(normal, 0.0f)));

                // Set the material
                ray->intersectionInfo->material = material;
                intersectionFound = true;
            }


        }
    }

    return intersectionFound;
}

