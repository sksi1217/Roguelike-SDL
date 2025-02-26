#include "Collider.h"
#include <utility>
#include <cmath>

// Конструктор
Collider::Collider(int x, int y, int w, int h) : rect({ x, y, w, h }) {}

// Обновление позиции коллайдера
void Collider::UpdatePosition(float objX, float objY, int offsetX, int offsetY) {
    rect.x = static_cast<int>(objX + offsetX);
    rect.y = static_cast<int>(objY + offsetY);
}

// Проверка столкновения с другим коллайдером
bool Collider::CheckCollision(const Collider& other) const {
    return !(rect.x + rect.w <= other.rect.x ||
        other.rect.x + other.rect.w <= rect.x ||
        rect.y + rect.h <= other.rect.y ||
        other.rect.y + other.rect.h <= rect.y);
}

// Метод для разрешения столкновений
void Collider::ResolveCollision(const Collider& other, float dx, float dy, float& objX, float& objY) {
    if (!CheckCollision(other)) return;

    int overlapX = std::min(
        rect.x + rect.w - other.rect.x,
        other.rect.x + other.rect.w - rect.x
    );

    int overlapY = std::min(
        rect.y + rect.h - other.rect.y,
        other.rect.y + other.rect.h - rect.y
    );

    if (std::abs(overlapX) < std::abs(overlapY)) {
        if (dx > 0) {
            objX = other.rect.x - rect.w; // Отталкивание влево
        }
        else if (dx < 0) {
            objX = other.rect.x + other.rect.w; // Отталкивание вправо
        }
    }
    else {
        if (dy > 0) {
            objY = other.rect.y - rect.h; // Отталкивание вверх
        }
        else if (dy < 0) {
            objY = other.rect.y + other.rect.h; // Отталкивание вниз
        }
    }
}