#include "Projectile.h"

Projectile::Projectile(SDL_Texture* texture, SDL_FPoint startPosition, SDL_FPoint velocity, float damage, float lifetime)
    : GameObject() {
    Texture = texture;
    Position = startPosition;
    Velocity = velocity;
    Damage = damage;
    Lifetime = lifetime;
    CurrentLifetime = 0.0f;
    IsActive = true;
    IsCollidable = true;
}

Projectile::~Projectile() {};



void Projectile::Update(float deltaTime) {
    if (CurrentLifetime >= Lifetime) {
        IsActive = false; // Пуля исчезает после истечения времени жизни
        return;
    }

    // Обновление позиции пули
    Position.x += Velocity.x * deltaTime;
    Position.y += Velocity.y * deltaTime;

    // Увеличение времени жизни
    CurrentLifetime += deltaTime;

    // Обновление коллайдера
    ColliderPosition();
}