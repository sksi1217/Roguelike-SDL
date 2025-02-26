#pragma once

#include "../Abstracts/GameObject.h"
#include "../Abstracts/Weapon.h"
#include <SDL.h>
#include <unordered_set>
#include <vector>
#include "../Textures/Animation.h"

class Player : public GameObject {
public:
    Player(SDL_Texture* texture, SDL_FPoint startPosition);
    void Update(float deltaTime) override;

private:
    void HandleMovementInput(const Uint8* keyboardState, SDL_FPoint& velocity);
    void UpdateSpriteRow(const SDL_FPoint& velocity);
    void HandleCollisions();

    enum Direction {
        DownRow = 1,
        UpRow = 2,
        RightRow = 3,
        LeftRow = 4, 
    };

    std::vector<Weapon*> weapons;
};