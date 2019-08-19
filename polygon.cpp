#include "polygon.h"
#define EPSILON 0.000001

bool Polygon::FindIntersection(std::shared_ptr<Ray> ray) {
    bool intersectionFound = false;

    // Object space ray origin and direction
    glm::vec3 objectSpaceRayOrigin = (*invModelMatrix) * glm::vec4(ray->rayOrigin, 1.0f);
    glm::vec3 objectSpaceRayDirection = glm::vec3((*invModelMatrix) * glm::vec4(ray->rayDirection, 0.0f));

    // Iterate through each traiangle inside the mesh and find the closest intersection with the ray
    for (unsigned int triangleIndex = 0; triangleIndex < triangulatedMeshIndixes.size(); triangleIndex+=3) {
        glm::vec3 vertexPos0 = meshPoints[triangulatedMeshIndixes[triangleIndex]];
        glm::vec3 vertexPos1 = meshPoints[triangulatedMeshIndixes[triangleIndex + 1]];
        glm::vec3 vertexPos2 = meshPoints[triangulatedMeshIndixes[triangleIndex + 2]];

        // We will calculate the world normal for the triangle
        // If backface culling is on and the triangle is facing the other direction we do not perform the intersection test
        glm::vec3 normal;
        glm::vec3 e1 = vertexPos0 - vertexPos1;
        glm::vec3 e2 = vertexPos0 - vertexPos2;
        if (clockwiseTriangulation) {
            normal = glm::normalize(glm::cross(e1, e2));
        } else {
            normal = glm::normalize(glm::cross(e2, e1));
        }

        if (backfaceCulling && glm::dot(normal, objectSpaceRayDirection) > 0) {
            continue;
        }

        // Calculate the intersection with the traingle
        glm::vec3 edge1, edge2, T, P, Q;
        double det, inv_det, U, V, parameterDistance;

        // find the edge that is shared by the two vertex positions with the vertex0
        edge1 = vertexPos1 - vertexPos0;
        edge2 = vertexPos2 - vertexPos0;

        // We will start the process of calculating the determinant (also useful for calcualting the U parameter in the UV's)
        P = glm::cross(edge2, objectSpaceRayDirection);

        // If the det is near zero the ray lies in plane of the triangle
        det = glm::dot(edge1, P);

        if (backfaceCulling) {
            if (det < EPSILON) {
                continue;
            } else {
                // Calculate distance from vertexPos0 to ray origin
                T = objectSpaceRayOrigin - vertexPos0;

                // Calculate the U value and check if in bounds of the traingle
                U = glm::dot(T, P);
                if (U < 0.0f || U > det) {
                    continue;
                } else {
                    // we will not check if we are inside the V parameter
                    Q = glm::cross(edge1, T);

                    V = glm::dot(objectSpaceRayDirection, Q);

                    if (V < 0.0f || (U + V) > det) {
                        continue;
                    } else {
                        // Calculate the parameterDistance
                        parameterDistance = glm::dot(edge2, Q);
                        inv_det = 1.0f / det;
                        parameterDistance *= inv_det;
                        intersectionFound = true;
                    }
                }
            }
        } else {
            if (det > -EPSILON && det < EPSILON) {
                continue;
            } else {
                inv_det = 1.0f / det;
                T = objectSpaceRayOrigin - vertexPos0;

                // Calculate and test if the U parameter is in bounds
                U = glm::dot(T, P) * inv_det;
                if (U < 0.0f || U > 1.0f) {
                    continue;
                } else {
                    // Calculate and test if the V parameter is in bounds
                    Q = glm::cross(edge1, T);
                    V = glm::dot(objectSpaceRayDirection, Q) * inv_det;
                    if (V < 0.0f || (U + V) > 1.0f) {
                        continue;
                    } else {
                        // calculate the parameterDistance
                        parameterDistance = glm::dot(edge2, Q) * inv_det;
                        intersectionFound = true;
                    }
                }
            }
        }

        if (intersectionFound) {
            // we will check if the parameter distance is set
            if (ray->intersectionInfo == NULL) {
                ray->intersectionInfo = std::make_shared<Intersect>();
                ray->intersectionInfo->parameterDistance = FLT_MAX;
            }

            if (parameterDistance < ray->intersectionInfo->parameterDistance) {
                ray->intersectionInfo->parameterDistance = parameterDistance;
            }

            // calculate and store the normal in world space
            ray->intersectionInfo->worldSpaceIntersectionNormal = glm::normalize(glm::vec3(glm::transpose(*invModelMatrix) * glm::vec4(normal, 0.0f)));;
        }
    }

    return intersectionFound;
}
