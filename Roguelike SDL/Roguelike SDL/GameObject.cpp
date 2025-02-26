#include "GameObject.h"
#include "Animation.h" // ���������� ����� Animation
#include "Collider.h" // ���������� ����� Collider
#include <iostream>
#include <SDL_image.h>

// �����������
GameObject::GameObject() {}

// ����������
GameObject::~GameObject() {
    if (Texture) {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
}

// ���������� ��������� �������
void GameObject::Update(float deltaTime) {
    UpdateCollider(); // ��������� ������� ����������
}

// ���������� ������� ����������
void GameObject::UpdateCollider() {
    if (IsCollidable) {
        Collider.x = static_cast<int>(Position.x + OffsetColliderX);
        Collider.y = static_cast<int>(Position.y + OffsetColliderY);
        Collider.w = WidthColliderX;
        Collider.h = HeightColliderY;
    }
}

// ����� ��� ���������� ������������
void GameObject::ResolveCollision(GameObject* other) {
    if (!IsCollidable || !other->IsCollidable) return;

    const SDL_Rect& playerCollider = Collider;
    const SDL_Rect& otherCollider = other->Collider;

    // ��������� ����������� ������������
    int overlapX = std::min(
        playerCollider.x + playerCollider.w - otherCollider.x,
        otherCollider.x + otherCollider.w - playerCollider.x
    );

    int overlapY = std::min(
        playerCollider.y + playerCollider.h - otherCollider.y,
        otherCollider.y + otherCollider.h - playerCollider.y
    );

    // ����������, � ����� ������� ��������� ������������
    if (overlapX > overlapY) {
        if (playerCollider.y < otherCollider.y) {
            Position.y -= overlapY; // ������������ ������
        }
        else {
            Position.y += overlapY; // ������������ �����
        }
    }
    else {
        if (playerCollider.x < otherCollider.x) {
            Position.x -= overlapX; // ������������ �����
        }
        else {
            Position.x += overlapX; // ������������ ������
        }
    }

    // ��������� ������� ���������� ����� ���������� ������������
    UpdateCollider();
}

// �������� ������������ � ������ ��������
bool GameObject::CheckCollision(const GameObject& other) const {
    if (!IsCollidable || !other.IsCollidable) return false;

    const SDL_Rect& rectA = Collider;
    const SDL_Rect& rectB = other.Collider;

    return !(rectA.x + rectA.w <= rectB.x ||
        rectB.x + rectB.w <= rectA.x ||
        rectA.y + rectA.h <= rectB.y ||
        rectB.y + rectB.h <= rectA.y);
}

// ��������� ������������
void GameObject::OnTriggerEnter(GameObject* object) {}

// �������� ��� ��������������
void GameObject::Action(GameObject* object) {}

// ��������� �������
void GameObject::Draw(SDL_Renderer* renderer, const Camera& camera) {
    if (!IsActive || !IsVisible || !Texture) return;

    // �������� ������� ��������
    int textureWidth, textureHeight;
    SDL_QueryTexture(Texture, nullptr, nullptr, &textureWidth, &textureHeight);

    // �������� ������� ������� �� ��������
    int frameWidth = animation ? animation->FrameWidth : textureWidth;
    int frameHeight = animation ? animation->FrameHeight : textureHeight;

    // ������ ������������� ��� ��������� � ��������� �������
    SDL_FRect destRect = {
        (Position.x - camera.Position.x) - Origin.x * Scale,
        (Position.y - camera.Position.y) - Origin.y * Scale,
        static_cast<float>(frameWidth * Scale),
        static_cast<float>(frameHeight * Scale)
    };

    // ����� ���������
    SDL_RendererFlip flip = FlipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // ������������ ��������
    SDL_SetTextureColorMod(Texture, TintColor.r, TintColor.g, TintColor.b);
    SDL_SetTextureAlphaMod(Texture, TintColor.a);

    if (animation) {
        // ����������� sourceRect � SDL_FRect
        SDL_Rect sourceRect = animation->GetCurrentFrameRectangle(SpriteRow);
        SDL_RenderCopyExF(renderer, Texture, &sourceRect, &destRect, Rotation, &Origin, flip);
    }
    else {
        SDL_RenderCopyExF(renderer, Texture, nullptr, &destRect, Rotation, &Origin, flip);
    }


    if (IsCollidable) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // ������ ����
        SDL_Rect colliderRect = {
            static_cast<int>(Collider.x - camera.Position.x),
            static_cast<int>(Collider.y - camera.Position.y),
            Collider.w,
            Collider.h
        };
        SDL_RenderDrawRect(renderer, &colliderRect);
    }


}