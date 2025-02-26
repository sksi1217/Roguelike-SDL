#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <string>
#include "Camera.h"

class Animation; // Прототип класса Animation

class GameObject {
public:
    // Основные характеристики объекта
    SDL_FPoint Position = { 0.0f, 0.0f }; // Позиция объекта
    SDL_Texture* Texture = nullptr;     // Текстура объекта
    SDL_Color TintColor = { 255, 255, 255, 255 }; // Цвет отрисовки (RGBA)
    float Speed = 0.0f;                 // Скорость движения (пикселей/секунду)
    float SlowFactor = 1.0f;            // Коэффициент замедления (1 = нормальная скорость)

    // Для отрисовки
    double Rotation = 0.0;              // Угол поворота (в радианах)
    SDL_FPoint Origin = { 0.0f, 0.0f };   // Точка поворота
    float Scale = 1.0f;                 // Масштаб
    bool FlipHorizontal = false;        // Отражение по горизонтали

    
    // Коллайдер
    SDL_Rect Collider;   // Коллайдер объекта
    int OffsetColliderX = 0;            // Смещение коллайдера по X
    int OffsetColliderY = 0;            // Смещение коллайдера по Y
    int WidthColliderX = 0;            // Размер коллайдера по X
    int HeightColliderY = 0;            // Размер коллайдера по Y
    

    // Характеристики состояния
    bool IsActive = true;               // Активность объекта
    bool IsVisible = true;              // Видимость объекта
    bool IsCollidable = true;           // Может ли объект сталкиваться
    bool IsStatic = false;              // Является ли объект статичным

    // Характеристики эффектов
    float PushForce = 1.0f;             // Сила отталкивания
    float Mass = 10.0f;                 // Масса объекта

    // Анимация
    Animation* animation = nullptr;     // Указатель на анимацию
    int SpriteRow = 0;                  // Номер строки спрайтов

    // Конструктор и деструктор
    GameObject();
    virtual ~GameObject();

    // Обновление состояния объекта
    virtual void Update(float deltaTime);

    // Обработка столкновений
    virtual void OnTriggerEnter(GameObject* object);

    // Действие при взаимодействии
    virtual void Action(GameObject* object);

    // Отрисовка объекта
    void Draw(SDL_Renderer* renderer, const Camera& camera);

    // Метод для проверки столкновения
    void ResolveCollision(GameObject* other);

    // Методы для работы с коллайдером
    void UpdateCollider(); // Обновляет позицию коллайдера
    bool CheckCollision(const GameObject& other) const; // Проверяет столкновение с другим объектом
};

#endif // GAMEOBJECT_H