// MagicStick.cpp
#include "MagicStick.h"
#include <iostream>

MagicStick::MagicStick(SDL_Texture* textureBullet, SDL_FPoint position)
{
    if (textureBullet == nullptr) return;

    TextureBullet = textureBullet;
    Position = position;

    Shells = 8; // Количество пуль в залпе
    FireRate = 2.0f; // Интервал между залпами (в секундах)
    BulletInterval = 0.4f; // Интервал между пулами внутри залпа (в секундах)
    Speed = 100; // Скорость пуль
}

void MagicStick::Shoot(float deltaTime) {
    if (nearestEnemy == nullptr) return; // Если нет ближайшего врага, выходим

    // Увеличиваем прошедшее время
    ElapsedTime += deltaTime;

    // Если не идёт залп и прошло достаточно времени для начала нового залпа
    if (!IsFiringZalp && ElapsedTime >= FireRate) {
        IsFiringZalp = true;            // Начинаем новый залп
        ShellsToFire = Shells;          // Инициализируем счётчик пуль для текущего залпа
        ElapsedTime = 0;                // Сбрасываем таймер
    }

    // Если идёт залп, проверяем, можно ли выпустить следующую пулю
    if (IsFiringZalp && ElapsedTime >= BulletInterval && ShellsToFire > 0) {
        // Создаём одну пулю
        SDL_FPoint direction = Help::Normalize(Help::Subtract(nearestEnemy->Position, Position)); // Нормализуем направление

        auto bullet = std::make_unique<MagicSphere>(
            GetTextureBullet(), // Используем текстуру из базового класса
            Position,
            direction,
            // Help::Multiply(direction, Speed),
            CalculateDamage(),
            4
        );

        // Добавляем пулю в список объектов игры
        ManagerGame::gameObjects.push_back(bullet.release()); // Передаем владение пулей менеджеру

        // Уменьшаем счётчик оставшихся пуль
        ShellsToFire--;
        ElapsedTime = 0; // Сбрасываем таймер для следующей пули
    }

    // Если все пули из залпа выпущены, завершаем залп
    if (ShellsToFire <= 0) {
        IsFiringZalp = false; // Завершаем залп
    }
}