#include "EnemySkelet.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "../Statics/ManagerGame.h"

EnemySkelet::EnemySkelet(SDL_Texture* texture, SDL_FPoint startPosition)
    : GameObject()
{
    if (!texture) {
        throw std::invalid_argument("Texture cannot be null.");
    }

    Texture = texture;
    Position = startPosition;
    Speed = 0.0f;

    Mass = 1;

    Scale = 1;
    Origin = { 8 , 8 };

    animation = new Animation(16, 16, 8, 1.0f / (Speed * 0.1f));

    OffsetColliderX = -4;
    OffsetColliderY = 4;
    WidthColliderX = 8;
    HeightColliderY = 4;
}

void EnemySkelet::UpdatePosPlr(SDL_FPoint& plrPosition)
{
    _playerPos = plrPosition;
}

void EnemySkelet::Update(float deltaTime) {
    direction = { _playerPos.x - Position.x, _playerPos.y - Position.y };
    NormalizeDirection();

    HandleMovement(deltaTime);
    HandleCollisions();

    bool isMoving = (direction.x != 0.0f || direction.y != 0.0f);
    animation->Update(isMoving, static_cast<Uint32>(deltaTime * 1000.0f));
}

void EnemySkelet::NormalizeDirection() {
    float length = std::hypot(direction.x, direction.y); // Более точная замена sqrt(x^2 + y^2)
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;

        if (std::abs(direction.x) > std::abs(direction.y)) {
            SpriteRow = (direction.x > 0 ? RightRow : LeftRow);
        }
        else {
            SpriteRow = (direction.y > 0 ? DownRow : UpRow);
        }
    }
}

void EnemySkelet::HandleMovement(float deltaTime) {
    Position.x += direction.x * Speed * deltaTime;
    Position.y += direction.y * Speed * deltaTime;
    ColliderPosition(); // Обновляем позицию коллайдера
}

void EnemySkelet::HandleCollisions() {
    for (auto obj : ManagerGame::gameObjects) {
        if (obj != this && CheckCollision(*obj)) {
            ResolveCollision(obj);
            break;
        }
    }
}