// Camera.cpp
#include "Camera.h"

Camera::Camera(SDL_FPoint Size, float speed) : Position{ 0.0f, 0.0f }, Size{ 800, 600 }, smoothSpeed(speed) {}

void Camera::UpdateCamera(SDL_FPoint& playerPosition, float deltaTime) {
    float targetX = playerPosition.x - Size.x / 2;
    float targetY = playerPosition.y - Size.y / 2;

    // »нтерпол€ци€ (плавное движение)
    Position.x += (targetX - Position.x) * smoothSpeed * deltaTime;
    Position.y += (targetY - Position.y) * smoothSpeed * deltaTime;
}