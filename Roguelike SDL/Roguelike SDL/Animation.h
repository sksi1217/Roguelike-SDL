#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <cstdint>

class Animation {
public:
    // Размер одного спрайта
    int FrameWidth;
    int FrameHeight;

    // Анимация
    int CurrentFrame; // Текущий кадр
    int TotalFrames;  // Общее количество кадров
    float TimePerFrame; // Время между кадрами (в секундах)
    float ElapsedTime;  // Прошедшее время для текущего кадра

    // Флаг для определения, движется ли объект
    bool IsPlaying;

    // Конструктор
    Animation(int frameWidth, int frameHeight, int totalFrames, float timePerFrame);

    // Обновление анимации
    void Update(bool isMoving, Uint32 deltaTime);

    // Получение прямоугольника текущего кадра
    SDL_Rect GetCurrentFrameRectangle(int spriteRow) const;
};

#endif // ANIMATION_H