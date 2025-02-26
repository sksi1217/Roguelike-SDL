#pragma once
#include <random>
#include "GameObject.h"


class Weapon : public GameObject {
public:

    float LastShotTime = 0.0f; // Время последнего выстрела

    // Основные характеристики оружия
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



    virtual ~Weapon() {}

    // Метод для стрельбы
    virtual void Shoot(std::vector<std::shared_ptr<GameObject>>& bullets, SDL_FPoint direction) {
        if (CanFire()) {
            // Создаем пулю
            std::shared_ptr<GameObject> bullet = CreateProjectile(direction);
            if (bullet) {
                bullets.push_back(bullet);
                LastShotTime = 0.0f; // Сброс времени до следующего выстрела
            }
        }
    }


    // Метод для нанесения урона
    float CalculateDamage() {
        float totalDamage = Damage;
        if (IsCriticalHit()) {
            totalDamage *= CriticalMultiplier;
        }
        return totalDamage;
    }

    // Проверка критического удара
    bool IsCriticalHit() {
        return NextFloat() < CriticalChance;
    }

    // Поиск ближайшего врага
    GameObject* FindNearestEnemy(const std::vector<GameObject*>& enemies) {
        GameObject* nearestEnemy = nullptr;
        float minDistance = std::numeric_limits<float>::max();

        for (const auto& obj : enemies) {
            if (!obj->IsActive) continue;

            float distance = Help::Distance(Position, obj->Position);
            if (distance < Range && distance < minDistance) {
                minDistance = distance;
                nearestEnemy = obj;
            }
        }

        return nearestEnemy;
    }

protected:
    virtual std::shared_ptr<GameObject> CreateProjectile(SDL_FPoint direction) = 0;

    // Генерация случайного числа от 0 до 1
    float NextFloat() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0f, 1.0f);
        return dis(gen);
    }

    bool CanFire() const {
        return LastShotTime >= FireRate;
    }

    

private:
    int Damage = 1; // Базовый урон
    float CriticalChance = 0.05f; // Шанс критического удара
    float CriticalMultiplier = 2.0f; // Множитель критического удара
    float Range = 300.0f; // Дальность атаки

    int Shells = 1; // Кол-во снарядов
    float FireRate = 2.0f; // Интервал между залпами (в секундах)
    float BulletInterval = 0.4f; // Интервал между пулями внутри залпа (в секундах)

    GameObject* nearestEnemy;
};