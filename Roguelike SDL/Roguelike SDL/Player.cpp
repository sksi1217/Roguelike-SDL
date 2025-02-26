#include "Player.h"

#include <cmath>
#include <iostream>
#include "ManagerGame.h"

// �����������
Player::Player(SDL_Texture* texture, SDL_FPoint startPosition)
    : GameObject() {
    if (!texture) {
        throw std::invalid_argument("Texture cannot be null.");
    }

    Texture = texture;
    Position = startPosition;
    Speed = 150.0f;

    Scale = 5;
    Origin = { 8 , 16 };

    SpriteRow = 0;

    // ������������� ��������
    animation = new Animation(16, 16, 8, 1.0f / (Speed * 0.1f));

    OffsetColliderX = -20;
    OffsetColliderY = -30;
    WidthColliderX = 40;
    HeightColliderY = 30;
}

// ���������� ���������
void Player::Update(float deltaTime) {
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL); // �������� ��������� ������
    SDL_FPoint velocity = { 0.0f, 0.0f };

    HandleMovementInput(keyboardState, velocity);

    // ��������� ���������� ������� ��� ������ ��� ������������
    SDL_FPoint previousPosition = Position;

    // ��������� ������� ������
    Position.x += velocity.x * Speed * deltaTime;
    Position.y += velocity.y * Speed * deltaTime;

    bool isMoving = (velocity.x != 0.0f || velocity.y != 0.0f);
    animation->Update(isMoving, static_cast<Uint32>(deltaTime * 1000.0f));

    

    // ��������� ������������ � ������� ���������
    for (auto obj : ManagerGame::gameObjects) {
        if (obj != this && CheckCollision(*obj)) {
            // ���������� ��������
            Position = previousPosition;
            ResolveCollision(obj);
            break; // ���������� �������� ����� ������� ������������
        }
    }

    // ��������� ������� ����������
    UpdateCollider();
}

// ��������� ����� ��� ��������
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
// ���������� ������ ������� ��� ��������
void Player::UpdateSpriteRow(const SDL_FPoint& velocity) {
    if (std::abs(velocity.x) > std::abs(velocity.y)) {
        SpriteRow = (velocity.x > 0.0f) ? RightRow : LeftRow;
    }
    else {
        SpriteRow = (velocity.y > 0.0f) ? DownRow : UpRow;
    }
}