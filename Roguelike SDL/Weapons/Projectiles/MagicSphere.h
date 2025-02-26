#pragma once
#include "../../Abstracts/Projectile.h"

class MagicSphere : public Projectile {
public:
    MagicSphere(SDL_Texture* texture, SDL_FPoint startPosition, SDL_FPoint velocity, float damage, float lifetime)
        : Projectile(texture, startPosition, velocity, damage, lifetime) {
    }
};