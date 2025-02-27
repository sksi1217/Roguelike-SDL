// MagicSphere.h
#pragma once
#include "../../Abstracts/Projectile.h"

class MagicSphere : public Projectile {
public:
	MagicSphere(
		SDL_Texture* texBull,
		const SDL_FPoint& startPosition,
		const SDL_FPoint& targetPosition,
		const float damage,
		const float lifetime
	) : Projectile(
		texBull,
		startPosition,
		targetPosition,
		damage,
		lifetime
	) {}

};