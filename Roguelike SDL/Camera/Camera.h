// Camera.h
#pragma once
#include <SDL.h>
class Camera {
public:
    Camera(SDL_FPoint Size, float speed);
    void UpdateCamera(SDL_FPoint& playerPosition, float deltaTime);
    void ZoomIn();
    void ZoomOut();
    SDL_FPoint GetPosition() const { return Position; }
    float GetScale() const { return scale; }
private:
    SDL_FPoint Position;
    SDL_FPoint Size;
    float smoothSpeed;
    float scale;
};