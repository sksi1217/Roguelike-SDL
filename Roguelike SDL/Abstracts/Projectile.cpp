// Projectile.cpp
#include "Projectile.h"
#include <iostream>

Projectile::Projectile(SDL_Texture* texture, SDL_FPoint position, SDL_FPoint velocity, int damage, float lifetime)
{
    if (texture == nullptr) std::cerr << "Failed texture: " << SDL_GetError() << std::endl; return;
    if (lifetime <= 0) std::cerr << "Failed lifetime: " << SDL_GetError() << std::endl; return;

    // Присваивания значения
    Texture = texture;
    Position = position;
    Speed = 10;
    Damage = damage;
    Lifetime = lifetime;

    // Стандартные настройки
    Origin = { 8, 8 };
    Scale = 0.5f;
    Position = position;
}

void Projectile::Update(float deltaTime) {
    if (!IsActive) return;

    // Обновляем текущее время жизни
    CurrentLifetime += deltaTime;
    if (CurrentLifetime >= Lifetime) {
        IsActive = false;
        return;
    }

    // Обновляем позицию пули
    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;

    // Проверяем столкновения

}