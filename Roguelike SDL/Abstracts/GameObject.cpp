#include "GameObject.h"
#include "../Textures/Animation.h"
#include <iostream>
#include <SDL_image.h>

GameObject::GameObject() {}

GameObject::~GameObject() {
    if (Texture) {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
}

// Updating the state of the object
void GameObject::Update(float deltaTime) {
    ColliderPosition(); // ��������� ������� ����������
}

// A method for collision resolution
void GameObject::ResolveCollision(GameObject* other) {
    if (!IsCollidable || !other->IsCollidable) return;
    const SDL_Rect& playerCollider = Collider;
    const SDL_Rect& otherCollider = other->Collider;
    int overlapX = std::min(playerCollider.x + playerCollider.w - otherCollider.x, otherCollider.x + otherCollider.w - playerCollider.x);
    int overlapY = std::min(playerCollider.y + playerCollider.h - otherCollider.y, otherCollider.y + otherCollider.h - playerCollider.y);
    if (overlapX < overlapY) {
        if (playerCollider.x < otherCollider.x) {
            ApplyRepulsion(this, other);
            Position.x -= overlapX; // Collision from the left
        } else {
            ApplyRepulsion(this, other);
            Position.x += overlapX; // Collision from the right
        }
    } else {
        if (playerCollider.y < otherCollider.y) {
            ApplyRepulsion(this, other);
            Position.y -= overlapY; // Collision from above
        } else {
            ApplyRepulsion(this, other);
            Position.y += overlapY; // Collision from below
        }
    }
    ColliderPosition(); // Update collider position after resolution
}


// Updating the collider's position
void GameObject::ColliderPosition() {
    if (IsCollidable) {
        Collider.x = (Position.x + OffsetColliderX);
        Collider.y = (Position.y + OffsetColliderY);
        Collider.w = WidthColliderX;
        Collider.h = HeightColliderY;
    }
}

// Checking collision with another object
bool GameObject::CheckCollision(const GameObject& other) const {
    if (!IsCollidable || !other.IsCollidable) return false;

    const SDL_Rect& rectA = Collider;
    const SDL_Rect& rectB = other.Collider;

    return !(rectA.x + rectA.w <= rectB.x ||
        rectB.x + rectB.w <= rectA.x ||
        rectA.y + rectA.h <= rectB.y ||
        rectB.y + rectB.h <= rectA.y);
}

// Collision handling
void GameObject::OnTriggerEnter(GameObject* object) {}

// Collision handling
void GameObject::Action(GameObject* object) {}

void GameObject::ApplyRepulsion(GameObject* obj, GameObject* other) {
    // ������ ����������� � ���������� ����� ���������
    SDL_FPoint direction = GameObject::Subtract(obj->Position, other->Position);
    float distance = Length(direction);

    if (distance == 0.0f) {
        distance = 0.001f; // �������� ������� �� ����
    }

    direction = Normalize(direction); // ����������� ������ �����������

    // ���� ������������ ��������������� ������ ��������
    float combinedMass = obj->Mass + other->Mass;
    float force = obj->PushForce * (obj->Mass / combinedMass);

    // ��������� ���� � ����� ��������
    SDL_FPoint pushVector = Multiply(direction, force);

    obj->Position = Add(obj->Position, pushVector);
    other->Position = Subtract(other->Position, Multiply(pushVector, other->Mass / obj->Mass));
}

// Object rendering
void GameObject::Draw(SDL_Renderer* renderer, const Camera& camera) {
    if (!IsActive || !IsVisible || !Texture) return;

    // Get the dimensions of the texture
    int textureWidth, textureHeight;
    SDL_QueryTexture(Texture, nullptr, nullptr, &textureWidth, &textureHeight);

    // Get sprite dimensions from animation
    int frameWidth = animation ? animation->FrameWidth : textureWidth;
    int frameHeight = animation ? animation->FrameHeight : textureHeight;

    float cameraScale = camera.GetScale(); // Get the camera scale

    // Create a rectangle for floating point drawing
    SDL_FRect destRect = {
        (Position.x - camera.GetPosition().x) * cameraScale - Origin.x * Scale * cameraScale,
        (Position.y - camera.GetPosition().y) * cameraScale - Origin.y * Scale * cameraScale,
        static_cast<float>(frameWidth * Scale * cameraScale),
        static_cast<float>(frameHeight * Scale * cameraScale)
    };

    // Reflection flags
    SDL_RendererFlip flip = FlipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    // Calculate the rotation point (in pixels after scaling)
    SDL_FPoint rotationCenter = {
        Origin.x * Scale * cameraScale,
        Origin.y * Scale * cameraScale
    };

    // Drawing the texture
    SDL_SetTextureColorMod(Texture, TintColor.r, TintColor.g, TintColor.b);
    SDL_SetTextureAlphaMod(Texture, TintColor.a);

    if (animation) {
        // Convert sourceRect to SDL_FRect
        SDL_Rect sourceRect = animation->GetCurrentFrameRectangle(SpriteRow);
        SDL_RenderCopyExF(renderer, Texture, &sourceRect, &destRect, Rotation, &rotationCenter, flip);
    }
    else {
        SDL_RenderCopyExF(renderer, Texture, nullptr, &destRect, Rotation, &rotationCenter, flip);
    }


    if (IsCollidable) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect colliderRect = {
            ((Collider.x - camera.GetPosition().x) * cameraScale),
            ((Collider.y - camera.GetPosition().y) * cameraScale),
            (Collider.w * cameraScale),
            (Collider.h * cameraScale)
        };
        SDL_RenderDrawRect(renderer, &colliderRect);
    }
}