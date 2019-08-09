#ifndef CAMERA_H
#define CAMERA_H
#include "glm/vec4.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"

class Camera
{
public:
    Camera(float screenWidth, float screenHeight);

    void MoveCameraAboutTarget(float xDiv, float zDiv);

    glm::vec3 cameraPos;
    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection;
    glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight;
    glm::vec3 cameraUp;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    float fov; // degrees
    float nearClip, farClip;

    // Move the camera about a point in the scene
    float radius; // The radius of the sphere
    float camX, camZ; // These are the points on the sphere surrounding the point where we want to show our camera
};

#endif // CAMERA_H
