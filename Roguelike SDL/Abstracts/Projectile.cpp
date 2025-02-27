#include "Projectile.h"
#include <iostream>

Projectile::Projectile(
	SDL_Texture* texBull,
	const SDL_FPoint& startPosition,
	const SDL_FPoint& targetPosition,
	const float damage,
	const float lifetime
) {

	Texture = texBull;
	Lifetime = lifetime;
	Position = startPosition;
	Scale = 0.5;
	Origin = { 8, 8 };

	// Вычисляем направление к цели
	float distanceX = targetPosition.x - startPosition.x;
	float distanceY = targetPosition.y - startPosition.y;
	float length = std::sqrt(distanceX * distanceX + distanceY * distanceY);

	// Нормализуем вектор и устанавливаем скорость
	Velocity.x = distanceX / length * 20.0f; // Скорость 5 пикселей/кадр
	Velocity.y = distanceY / length * 20.0f;


}


void Projectile::Update(float deltaTime)
{
	if (!IsActive) return;

	// Обновляем текущее время жизни
	CurrentLifetime += deltaTime;
	if (CurrentLifetime >= Lifetime) {
		IsActive = false; // Пуля исчезает после истечения времени жизни
		IsActive = false;
		CurrentLifetime = 0;
		return;
	}

	// Обновление позиции пули
	// Обновляем позицию пули
	Position.x += Velocity.x * deltaTime;
	Position.y += Velocity.y * deltaTime;


	// Обновление коллайдера
	ColliderPosition();
}