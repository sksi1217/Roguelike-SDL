#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>


class Game {
public:
    // Конструктор
    Game(const char* title, int width, int height);

    // Деструктор
    ~Game();

    // Главный игровой цикл
    void Run();
    
private:
    bool isRunning = true;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Инициализация
    void Initialize();

    // Загрузка ресурсов
    void LoadContent();

    // Обновление логики
    void Update(float deltaTime);

    // Отрисовка кадра
    void Draw();

    // Выгрузка ресурсов
    void UnloadContent();

    // Обработка событий
    void HandleEvents();
    // Проверка столкновений между объектами
    void CheckCollisions();
};

#endif // GAME