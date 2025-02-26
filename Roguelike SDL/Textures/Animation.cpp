#include "Animation.h"

// Конструктор
Animation::Animation(int frameWidth, int frameHeight, int totalFrames, float timePerFrame)
    : FrameWidth(frameWidth),
    FrameHeight(frameHeight),
    TotalFrames(totalFrames),
    TimePerFrame(timePerFrame),
    CurrentFrame(0),
    ElapsedTime(0.0f),
    IsPlaying(false) {
}

// Обновление анимации
void Animation::Update(bool isMoving, Uint32 deltaTime) {
    if (isMoving) {
        IsPlaying = true;

        // Добавляем прошедшее время
        ElapsedTime += static_cast<float>(deltaTime) / 1000.0f;

        // Проверяем, пора ли переходить к следующему кадру
        if (ElapsedTime >= TimePerFrame) {
            ElapsedTime -= TimePerFrame;
            CurrentFrame = (CurrentFrame + 1) % TotalFrames; // Циклический переход между кадрами
        }
    }
    else {
        IsPlaying = false;
    }
}

// Получение прямоугольника текущего кадра
SDL_Rect Animation::GetCurrentFrameRectangle(int spriteRow) const {
    return SDL_Rect{
        CurrentFrame * FrameWidth, // X координата
        spriteRow * FrameHeight,   // Y координата
        FrameWidth,                // Ширина
        FrameHeight                // Высота
    };
}