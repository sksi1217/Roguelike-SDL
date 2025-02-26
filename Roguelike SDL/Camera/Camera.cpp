// Camera.cpp
#include "Camera.h"

Camera::Camera(SDL_FPoint Size, float speed)
    : Position{ 0.0f, 0.0f }, Size{ Size.x, Size.y }, smoothSpeed(speed), scale(5.0f) {
}

void Camera::UpdateCamera(SDL_FPoint& playerPosition, float deltaTime) {
    float targetX = playerPosition.x - (Size.x / 2) / scale;
    float targetY = playerPosition.y - (Size.y / 2) / scale;
    Position.x += (targetX - Position.x) * smoothSpeed * deltaTime;
    Position.y += (targetY - Position.y) * smoothSpeed * deltaTime;
}

void Camera::ZoomIn() {
    if (scale < 5.0f) {
        scale += 0.1f;
    }
}

void Camera::ZoomOut() {
    if (scale > 3.0f) {
        scale -= 0.1f;
    }
}