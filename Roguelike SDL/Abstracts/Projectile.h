#pragma once
#include "GameObject.h"
#include <SDL.h> // Для SDL_FPoint

class Projectile : public GameObject {
public:
    Projectile(const SDL_FPoint& startPosition, const SDL_FPoint& targetPosition, SDL_Texture* texBull) {
        Position = startPosition;
        Texture = texBull;
        // Вычисляем направление к цели
        float distanceX = targetPosition.x - startPosition.x;
        float distanceY = targetPosition.y - startPosition.y;
        float length = std::sqrt(distanceX * distanceX + distanceY * distanceY);

        // Нормализуем вектор и устанавливаем скорость
        Velocity.x = distanceX / length * 20.0f; // Скорость 5 пикселей/кадр
        Velocity.y = distanceY / length * 20.0f;
    }

    void Update(float deltaTime) override {
        if (IsActive) {
            Position.x += Velocity.x * deltaTime;
            Position.y += Velocity.y * deltaTime;

            // Проверяем, вышел ли снаряд за пределы экрана
            if (Position.x < 0 || Position.x > 800 || Position.y < 0 || Position.y > 600) {
                IsActive = false; // Отмечаем объект как неактивный
            }
        }
    }
private:
    SDL_FPoint Velocity; // Вектор скорости снаряда
};