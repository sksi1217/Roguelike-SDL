// Weapon.h
#pragma once
#include <random>
#include "../Statics/ManagerGame.h"
#include "../Abstracts/Projectile.h"

#include <vector>
#include <iostream>
#include <memory> // Для std::unique_ptr
#include <SDL.h> // Для SDL_FPoint
#include "../Statics/Help.h"
#include "../Weapons/Projectiles/MagicSphere.h"

class Weapon {
public:
    Weapon(SDL_Texture* texBull) 
    {
        TextureBullet = texBull;
    };

    float Speed = 10; // Скорость пули
    int Damage = 1; // Базовый урон
    SDL_FPoint StartPosition = { 0, 0 }; // Позиция оружия
    SDL_Texture* TextureBullet = nullptr; // Текстура пули
    SDL_FPoint Velocity = { 0, 0 }; // Направление и скорость полета
    float CriticalChance = 0.05f; // Шанс критического удара
    float CriticalMultiplier = 2.0f; // Множитель критического удара
    float Range = 200.0f; // Дальность атаки
    int Shells = 1; // Кол-во снарядов
    float FireRate = 2.0f; // Интервал между залпами (в секундах)
    float BulletInterval = 0.4f; // Интервал между пулями внутри залпа (в секундах)
    int ShellsToFire = 0; // Оставшееся количество пуль в текущем залпе
    bool IsFiringZalp = false; // Флаг, указывающий, происходит ли залп

    float LifetimeBullet = 5.0f; // Время жизни пули
    float LastShotTime = 0.0f; // Время последнего выстрела
    float ElapsedTime = 0.0f; // Время, прошедшее с последнего выстрела
    GameObject* nearestEnemy = nullptr; // Ближайший враг


    void Shoot(const SDL_FPoint& Position) {
        nearestEnemy = FindNearestEnemy();
        if (TextureBullet == nullptr)
        {
            std::cout << "Error texture" << std::endl;
            return;
        }
            

        //if (nearestEnemy == nullptr) std::cout << "Error nearestEnemy" << std::endl; return;

        auto projectile = std::make_unique<MagicSphere>
            (
                TextureBullet,
                Position,
                nearestEnemy->Position,
                Damage,
                LifetimeBullet
            );
        ManagerGame::AddGameObject(std::move(projectile)); // Добавляем снаряд в менеджер игры
        std::cout << "Boom!" << std::endl;
    }

    // Метод для расчета урона
    float CalculateDamage();

    // Проверка критического удара
    bool IsCriticalHit() {
        return Help::NextFloat() < CriticalChance;
    }

    GameObject* FindNearestEnemy();

};