#pragma once
#ifndef GAME_H
#define GAME_H

#include "Abstracts/GameObject.h"
#include "Statics/ManagerGame.h"
#include "Models/EnemySkelet.h"
#include "Models/Player.h"
#include "Statics/Help.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>


class Game {
public:
    // Designer
    Game(const char* title, int width, int height);

    // Destructor
    ~Game();

    // Main Game Cycle
    void Run();
    
private:
    bool isRunning = true;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Initialization
    void Initialize();

    // Resource Loading
    void LoadContent();

    // Logic Update
    void Update(float deltaTime);

    // Frame rendering
    void Draw();

    // Resource offloading
    void UnloadContent();

    // Event Handling
    void HandleEvents();
};

#endif // GAME