#pragma once
#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>


class Game {
public:
    // �����������
    Game(const char* title, int width, int height);

    // ����������
    ~Game();

    // ������� ������� ����
    void Run();
    
private:
    bool isRunning = true;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // �������������
    void Initialize();

    // �������� ��������
    void LoadContent();

    // ���������� ������
    void Update(float deltaTime);

    // ��������� �����
    void Draw();

    // �������� ��������
    void UnloadContent();

    // ��������� �������
    void HandleEvents();
    // �������� ������������ ����� ���������
    void CheckCollisions();
};

#endif // GAME