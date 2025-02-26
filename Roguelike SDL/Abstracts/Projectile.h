#pragma once
#include "GameObject.h"
#include <SDL.h>

class Projectile : public GameObject {
public:
    // Конструктор с параметром velocity
    Projectile(SDL_Texture* texture, SDL_FPoint position, SDL_FPoint velocity, int damage, float lifetime);

    void Update(float deltaTime) override;

    int Damage; // Базовый урон
    float Lifetime; // Время жизни пули
    float CurrentLifetime = 0.0f; // Текущее время существования
    SDL_FPoint Velocity; // Направление и скорость полета
};