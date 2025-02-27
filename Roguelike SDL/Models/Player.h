#pragma once

#include "../Abstracts/GameObject.h"
#include "../Abstracts/Weapon.h"
#include <SDL.h>
#include <unordered_set>
#include <vector>
#include "../Textures/Animation.h"

class Player : public GameObject {
public:
    std::vector<std::unique_ptr<Weapon>> _allWeapons; // Используем unique_ptr

    Player(SDL_Texture* texture, SDL_FPoint startPosition);
    void Update(float deltaTime) override;

private:
    void HandleMovementInput(const Uint8* keyboardState, SDL_FPoint& velocity);
    void UpdateSpriteRow(const SDL_FPoint& velocity);
    void HandleCollisions();
    void HandleWeaponInteraction(float deltaTime);

    enum Direction {
        DownRow = 1,
        UpRow = 2,
        RightRow = 3,
        LeftRow = 4, 
    };
};