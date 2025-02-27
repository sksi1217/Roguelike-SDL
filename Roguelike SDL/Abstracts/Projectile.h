#pragma once
#include "GameObject.h"
#include <SDL.h> // Для SDL_FPoint
#include <iostream>

class Projectile : public GameObject {
public:
	Projectile(
		SDL_Texture* texBull,
		const SDL_FPoint& startPosition,
		const SDL_FPoint& targetPosition,
		const float damage,
		const float lifetime
	);

	~Projectile() {};

	void Update(float deltaTime) override;


protected:
	float CurrentLifetime = 0.0f; // Текущее время
	float Lifetime;
	SDL_FPoint Velocity; // Вектор скорости снаряда
};