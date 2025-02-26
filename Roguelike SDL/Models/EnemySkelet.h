#pragma once
#include "../Abstracts/GameObject.h"
#include <SDL.h>
#include "Player.h"

class EnemySkelet : public GameObject {
public:
    EnemySkelet(SDL_Texture* texture, SDL_FPoint startPosition);
    void Update(float deltaTime) override;
    void UpdatePosPlr(SDL_FPoint& plrPosition);

private:
    SDL_FPoint direction;
    SDL_FPoint _playerPos;

    enum Direction {
        DownRow = 1,
        UpRow = 2,
        RightRow = 3,
        LeftRow = 4,
    };

    void NormalizeDirection();
    void HandleMovement(float deltaTime);
    void HandleCollisions();

};