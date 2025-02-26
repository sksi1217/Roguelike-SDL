// Weapon.h
#pragma once
#include <random>
#include "GameObject.h"
#include "../Statics/Help.h"
#include "../Statics/ManagerGame.h"

class Weapon : public GameObject {
public:
    int Damage = 1; // Базовый урон
    SDL_FPoint StartPosition = { 0, 0 }; // Позиция оружия
    SDL_Texture* TextureBullet = nullptr; // Текстура пули
    float Speed = 10; // Скорость пули
    SDL_FPoint Velocity; // Направление и скорость полета
    float CriticalChance = 0.05f; // Шанс критического удара
    float CriticalMultiplier = 2.0f; // Множитель критического удара
    float Range = 300.0f; // Дальность атаки
    int Shells = 1; // Кол-во снарядов
    float FireRate = 2.0f; // Интервал между залпами (в секундах)
    float BulletInterval = 0.4f; // Интервал между пулями внутри залпа (в секундах)
    int ShellsToFire = 0; // Оставшееся количество пуль в текущем залпе
    bool IsFiringZalp = false; // Флаг, указывающий, происходит ли залп
    float LifetimeBullet = 2.0f; // Время жизни пули
    float LastShotTime = 0.0f; // Время последнего выстрела
    float ElapsedTime = 0.0f; // Время, прошедшее с последнего выстрела
    GameObject* nearestEnemy = nullptr; // Ближайший враг
    
    // Геттеры и сеттеры
    int GetDamage() const { return Damage; }
    void SetDamage(int value) { Damage = value; }
    float GetCriticalChance() const { return CriticalChance; }
    void SetCriticalChance(float value) { CriticalChance = value; }
    float GetCriticalMultiplier() const { return CriticalMultiplier; }
    void SetCriticalMultiplier(float value) { CriticalMultiplier = value; }
    float GetRange() const { return Range; }
    void SetRange(float value) { Range = value; }
    int GetShells() const { return Shells; }
    void SetShells(int value) { Shells = value; }
    float GetFireRate() const { return FireRate; }
    void SetFireRate(float value) { FireRate = value; }
    float GetBulletInterval() const { return BulletInterval; }
    void SetBulletInterval(float value) { BulletInterval = value; }

    // Геттер и сеттер для TextureBullet
    SDL_Texture* GetTextureBullet() const { return TextureBullet; }
    void SetTextureBullet(SDL_Texture* value) { TextureBullet = value; }

    // Метод для стрельбы
    virtual void Shoot(float deltaTime) = 0;

    // Метод для расчета урона
    float CalculateDamage();

    // Проверка критического удара
    bool IsCriticalHit() {
        return Help::NextFloat() < CriticalChance;
    }

    // Поиск ближайшего врага
    GameObject* FindNearestEnemy();
};