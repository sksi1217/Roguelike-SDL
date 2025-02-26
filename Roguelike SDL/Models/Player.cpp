﻿#include "Player.h"
#include <cmath>
#include <iostream>
#include "../Weapons/MagicStick.h"

//Weapon weapon; // Оружие персонажа
float ElapsedTime = 0;
SDL_Texture* BulletTexture;

Player::Player(SDL_Texture* texture, SDL_FPoint startPosition) : GameObject()
{
	if (!texture) {
		throw std::invalid_argument("Texture cannot be null.");
	}

	Texture = texture;
	Position = startPosition;
	Speed = 50.0f;

	Scale = 1;
	Origin = { 8 , 8 };

	SpriteRow = 0;

	animation = new Animation(16, 16, 8, 1.0f / (Speed * 0.1f));

	OffsetColliderX = -4;
	OffsetColliderY = 4;
	WidthColliderX = 8;
	HeightColliderY = 4;

	// MagicStick* _magicStick = new MagicStick(texture, { 50, 0 });

	// Используем unique_ptr для управления памятью
	// _allWeapons.emplace_back(std::make_unique<MagicStick>(texture, Position));
}

void Player::Update(float deltaTime) {
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	SDL_FPoint velocity = { 0.0f, 0.0f };

	HandleMovementInput(keyboardState, velocity);

	Position.x += velocity.x * Speed * deltaTime;
	Position.y += velocity.y * Speed * deltaTime;

	ColliderPosition();

	HandleCollisions();

	HandleWeaponInteraction(deltaTime);

	bool isMoving = (velocity.x != 0.0f || velocity.y != 0.0f);
	animation->Update(isMoving, static_cast<Uint32>(deltaTime * 1000.0f));
}

// Управлением персонажем
void Player::HandleMovementInput(const Uint8* keyboardState, SDL_FPoint& velocity) {
	if (keyboardState[SDL_SCANCODE_A]) velocity.x -= 1.0f;
	if (keyboardState[SDL_SCANCODE_D]) velocity.x += 1.0f;
	if (keyboardState[SDL_SCANCODE_W]) velocity.y -= 1.0f;
	if (keyboardState[SDL_SCANCODE_S]) velocity.y += 1.0f;

	if (velocity.x != 0.0f || velocity.y != 0.0f) {
		float length = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		velocity.x /= length;
		velocity.y /= length;

		UpdateSpriteRow(velocity);
	}
}

// Обновление спрайтов
void Player::UpdateSpriteRow(const SDL_FPoint& velocity) {
	if (std::abs(velocity.x) > std::abs(velocity.y)) {
		SpriteRow = (velocity.x > 0.0f) ? RightRow : LeftRow;
	}
	else {
		SpriteRow = (velocity.y > 0.0f) ? DownRow : UpRow;
	}
}

// Проверка на столкновение
void Player::HandleCollisions() {
	for (auto& objPtr : ManagerGame::gameObjects) {
		GameObject* obj = objPtr.get(); // Получаем сырой указатель на объект
		if (obj != nullptr && obj != this && CheckCollision(*obj)) {
			ResolveCollision(obj);
			break;
		}
	}
}

void Player::HandleWeaponInteraction(float deltaTime) {
	// Увеличиваем прошедшее время
	ElapsedTime += deltaTime;

	// Если не идёт залп и прошло достаточно времени для начала нового залпа
	if (ElapsedTime >= 1) {
		if (_allWeapons.size() > 0) {
			for (const auto& weaponPtr : _allWeapons) { // Итерация по unique_ptr
				if (!weaponPtr) continue; // Проверка на null-указатель

				// Обновляем позицию оружия
				// weaponPtr->Position = Position;

				// Находим ближайшего врага
				// weaponPtr->nearestEnemy = weaponPtr->FindNearestEnemy();

				// Выполняем выстрел
				weaponPtr->Shoot(Position);
			}
			ElapsedTime = 0;
		}
	}
}