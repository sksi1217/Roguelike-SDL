#pragma once
#include <SDL.h>

class Collider {
public:
    SDL_Rect rect; // Коллайдер как прямоугольник

    // Конструктор
    Collider(int x, int y, int w, int h);

    // Метод для обновления позиции коллайдера
    void UpdatePosition(float objX, float objY, int offsetX, int offsetY);

    // Проверка столкновения с другим коллайдером
    bool CheckCollision(const Collider& other) const;

    // Метод для разрешения столкновений
    void ResolveCollision(const Collider& other, float dx, float dy, float& objX, float& objY);
};