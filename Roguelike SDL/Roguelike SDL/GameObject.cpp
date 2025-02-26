#include "GameObject.h"
#include "Animation.h" // Подключаем класс Animation
#include "Collider.h" // Подключаем класс Collider
#include <iostream>
#include <SDL_image.h>

// Конструктор
GameObject::GameObject() {}

// Деструктор
GameObject::~GameObject() {
    if (Texture) {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
}

// Обновление состояния объекта
void GameObject::Update(float deltaTime) {
    UpdateCollider(); // Обновляем позицию коллайдера
}

// Обновление позиции коллайдера
void GameObject::UpdateCollider() {
    if (IsCollidable) {
        Collider.x = static_cast<int>(Position.x + OffsetColliderX);
        Collider.y = static_cast<int>(Position.y + OffsetColliderY);
        Collider.w = WidthColliderX;
        Collider.h = HeightColliderY;
    }
}

// Метод для разрешения столкновений
void GameObject::ResolveCollision(GameObject* other) {
    if (!IsCollidable || !other->IsCollidable) return;

    const SDL_Rect& playerCollider = Collider;
    const SDL_Rect& otherCollider = other->Collider;

    // Вычисляем направление столкновения
    int overlapX = std::min(
        playerCollider.x + playerCollider.w - otherCollider.x,
        otherCollider.x + otherCollider.w - playerCollider.x
    );

    int overlapY = std::min(
        playerCollider.y + playerCollider.h - otherCollider.y,
        otherCollider.y + otherCollider.h - playerCollider.y
    );

    // Определяем, с какой стороны произошло столкновение
    if (overlapX > overlapY) {
        if (playerCollider.y < otherCollider.y) {
            Position.y -= overlapY; // Столкновение сверху
        }
        else {
            Position.y += overlapY; // Столкновение снизу
        }
    }
    else {
        if (playerCollider.x < otherCollider.x) {
            Position.x -= overlapX; // Столкновение слева
        }
        else {
            Position.x += overlapX; // Столкновение справа
        }
    }

    // Обновляем позицию коллайдера после разрешения столкновения
    UpdateCollider();
}

// Проверка столкновения с другим объектом
bool GameObject::CheckCollision(const GameObject& other) const {
    if (!IsCollidable || !other.IsCollidable) return false;

    const SDL_Rect& rectA = Collider;
    const SDL_Rect& rectB = other.Collider;

    return !(rectA.x + rectA.w <= rectB.x ||
        rectB.x + rectB.w <= rectA.x ||
        rectA.y + rectA.h <= rectB.y ||
        rectB.y + rectB.h <= rectA.y);
}

// Обработка столкновений
void GameObject::OnTriggerEnter(GameObject* object) {}

// Действие при взаимодействии
void GameObject::Action(GameObject* object) {}

// Отрисовка объекта
void GameObject::Draw(SDL_Renderer* renderer, const Camera& camera) {
    if (!IsActive || !IsVisible || !Texture) return;

    // Получаем размеры текстуры
    int textureWidth, textureHeight;
    SDL_QueryTexture(Texture, nullptr, nullptr, &textureWidth, &textureHeight);

    // Получаем размеры спрайта из анимации
    int frameWidth = animation ? animation->FrameWidth : textureWidth;
    int frameHeight = animation ? animation->FrameHeight : textureHeight;

    // Создаём прямоугольник для отрисовки с плавающей запятой
    SDL_FRect destRect = {
        (Position.x - camera.Position.x) - Origin.x * Scale,
        (Position.y - camera.Position.y) - Origin.y * Scale,
        static_cast<float>(frameWidth * Scale),
        static_cast<float>(frameHeight * Scale)
    };

    // Флаги отражения
    SDL_RendererFlip flip = FlipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Отрисовываем текстуру
    SDL_SetTextureColorMod(Texture, TintColor.r, TintColor.g, TintColor.b);
    SDL_SetTextureAlphaMod(Texture, TintColor.a);

    if (animation) {
        // Преобразуем sourceRect в SDL_FRect
        SDL_Rect sourceRect = animation->GetCurrentFrameRectangle(SpriteRow);
        SDL_RenderCopyExF(renderer, Texture, &sourceRect, &destRect, Rotation, &Origin, flip);
    }
    else {
        SDL_RenderCopyExF(renderer, Texture, nullptr, &destRect, Rotation, &Origin, flip);
    }


    if (IsCollidable) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Зелёный цвет
        SDL_Rect colliderRect = {
            static_cast<int>(Collider.x - camera.Position.x),
            static_cast<int>(Collider.y - camera.Position.y),
            Collider.w,
            Collider.h
        };
        SDL_RenderDrawRect(renderer, &colliderRect);
    }


}