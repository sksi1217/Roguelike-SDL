// MagicStick.h
#pragma once
#include <SDL.h>
#include "../Abstracts/Weapon.h"
#include "../Statics/ManagerGame.h"
#include "Projectiles/MagicSphere.h"

class MagicStick : public Weapon {
public:
    MagicStick(SDL_Texture* TextureBullet, SDL_FPoint StartPosition);

    void Shoot(float deltaTime) override;
};