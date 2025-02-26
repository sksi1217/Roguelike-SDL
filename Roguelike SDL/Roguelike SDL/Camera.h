// Camera.h
#pragma once
#include <SDL.h>

class Camera {
public:
    Camera(SDL_FPoint Size, float speed);
    void UpdateCamera(SDL_FPoint& playerPosition, float deltaTime);

    SDL_FPoint Position;

private:
    SDL_FPoint Size;
    float smoothSpeed;
};