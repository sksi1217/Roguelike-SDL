#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SDL.h>
#include <unordered_set>
#include <vector>
#include "Animation.h"

class Player : public GameObject {
public:
    Player(SDL_Texture* texture, SDL_FPoint startPosition);
    void Update(float deltaTime) override;

private:
    void HandleMovementInput(const Uint8* keyboardState, SDL_FPoint& velocity);
    void UpdateSpriteRow(const SDL_FPoint& velocity);

    static constexpr int DownRow = 1;
    static constexpr int UpRow = 2;
    static constexpr int RightRow = 3;
    static constexpr int LeftRow = 4;

};

#endif // PLAYER_H