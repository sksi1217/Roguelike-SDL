// Weapon.h
#pragma once
#include <random>
#include "../Statics/ManagerGame.h"
#include "../Abstracts/Projectile.h"

#include <vector>
#include <iostream>
#include <memory> // Для std::unique_ptr
#include <SDL.h> // Для SDL_FPoint

class Weapon {
public:
    void shoot(const SDL_FPoint& startPosition, const SDL_FPoint& targetPosition, SDL_Texture* texBull) {
        auto projectile = std::make_unique<Projectile>(startPosition, targetPosition, texBull);
        ManagerGame::AddGameObject(std::move(projectile)); // Добавляем снаряд в менеджер игры
        std::cout << "asd" << std::endl;
    }
};