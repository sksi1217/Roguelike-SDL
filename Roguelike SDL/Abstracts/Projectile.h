#pragma once

#include "GameObject.h"
#include <SDL.h>

class Projectile : public GameObject {
public:
    Projectile(SDL_Texture* texture, SDL_FPoint startPosition, SDL_FPoint velocity, float damage, float lifetime);

    ~Projectile() {}

    void Update(float deltaTime) override;

    float GetDamage() const { return Damage; }

private:
    SDL_FPoint Velocity; // Направление и скорость полета
    float Damage; // Урон пули
    float Lifetime; // Время жизни пули
    float CurrentLifetime; // Текущее время существования
};