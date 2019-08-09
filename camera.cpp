#include "camera.h"

Camera::Camera(float screenWidth, float screenHeight) {
    cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    fov = 75.0f;
    nearClip = 0.1f;
    farClip = 100.0f;
    // This direction is pointing in the inverse direction of what it is pointing
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(UP, cameraDirection));
    cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
    modelMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(cameraPos, cameraTarget, UP);
    projectionMatrix = glm::perspective(glm::radians(fov), screenWidth / screenHeight, nearClip, farClip);
}

void Camera::MoveCameraAboutTarget(float xDiv, float zDiv) {
    camX = glm::sin(xDiv) * radius;
    camZ = glm::cos(zDiv) * radius;
    cameraPos.x = camX;
    cameraPos.z = camZ;
    viewMatrix = glm::lookAt(cameraPos, cameraTarget, UP);
}
