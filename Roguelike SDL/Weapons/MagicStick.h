#pragma once

#include <SDL.h>
#include "../Abstracts/Weapon.h"
#include "../Statics/Help.h"
#include "../Statics/Help.h"
#include "Projectiles/MagicSphere.h"


class MagicStick : public Weapon {
public:
    MagicStick(SDL_Texture* texture, SDL_FPoint position) { }

    void Shoot(float deltaTime) override {
        if (deltaTime - LastShotTime >= GetFireRate()) {
            LastShotTime = deltaTime;

            // Создание пули
            SDL_FPoint direction = { 0.0f, -1.0f }; // Направление полета пули
            GameObject* bullet = new GameObject();
            bullet->Texture = Texture;
            bullet->Position = Position;
            bullet->Velocity = Help::Multiply(direction, Speed); // Скорость пули
            bullet->IsActive = true;
            bullet->IsCollidable = true;

            // Добавление пули в список
            ManagerGame::bullets.push_back(std::shared_ptr<GameObject>(bullet));
        }
    }

protected:
    std::shared_ptr<GameObject> CreateProjectile(SDL_FPoint direction) override {
        SDL_FPoint velocity = { direction.x * Speed, direction.y * Speed };
        return std::make_shared<MagicSphere>(Texture, Position, velocity, CalculateDamage, 2.0f); // Создаем магическую сферу
    }
};
};