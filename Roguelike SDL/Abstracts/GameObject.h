#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <string>
#include <cmath>
#include "../Camera/Camera.h"

class Animation;

class GameObject {
public:
    // Main characteristics of the object
    SDL_FPoint Position = { 0.0f, 0.0f };
    SDL_Texture* Texture = nullptr;
    SDL_Color TintColor = { 255, 255, 255, 255 };
    float Speed = 0.0f;
    float SlowFactor = 1.0f;

    // To draw
    double Rotation = 0.0;
    SDL_FPoint Origin = { 0.0f, 0.0f };
    float Scale = 1.0f;
    bool FlipHorizontal = false;

    // Collider
    SDL_Rect Collider;
    int OffsetColliderX = 0;
    int OffsetColliderY = 0;
    int WidthColliderX = 0;
    int HeightColliderY = 0;

    // Tag
    int Tag = NULL;

    // State Characteristics
    bool IsActive = true;
    bool IsVisible = true;
    bool IsCollidable = true;
    bool IsStatic = false;

    // Effect Characteristics
    float PushForce = 1.0f;
    float Mass = 50.0f;

    // Animation
    Animation* animation = nullptr;
    int SpriteRow = 0;

    // Constructor and destructor
    GameObject();
    virtual ~GameObject();

    virtual void Update(float deltaTime);

    virtual void OnTriggerEnter(GameObject* object);

    virtual void Action(GameObject* object);

    // Object rendering
    void Draw(SDL_Renderer* renderer, const Camera& camera);

    // Method for collision testing
    void ResolveCollision(GameObject* other);

    // Methods for working with the collider
    void ColliderPosition(); // Updates the collider position
    bool CheckCollision(const GameObject& other) const; // Checks for collision with another object

    void ApplyRepulsion(GameObject* obj, GameObject* other);
};

#endif // GAMEOBJECT_H