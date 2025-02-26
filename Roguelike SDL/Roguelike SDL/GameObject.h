#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <string>
#include "Camera.h"

class Animation; // �������� ������ Animation

class GameObject {
public:
    // �������� �������������� �������
    SDL_FPoint Position = { 0.0f, 0.0f }; // ������� �������
    SDL_Texture* Texture = nullptr;     // �������� �������
    SDL_Color TintColor = { 255, 255, 255, 255 }; // ���� ��������� (RGBA)
    float Speed = 0.0f;                 // �������� �������� (��������/�������)
    float SlowFactor = 1.0f;            // ����������� ���������� (1 = ���������� ��������)

    // ��� ���������
    double Rotation = 0.0;              // ���� �������� (� ��������)
    SDL_FPoint Origin = { 0.0f, 0.0f };   // ����� ��������
    float Scale = 1.0f;                 // �������
    bool FlipHorizontal = false;        // ��������� �� �����������

    
    // ���������
    SDL_Rect Collider;   // ��������� �������
    int OffsetColliderX = 0;            // �������� ���������� �� X
    int OffsetColliderY = 0;            // �������� ���������� �� Y
    int WidthColliderX = 0;            // ������ ���������� �� X
    int HeightColliderY = 0;            // ������ ���������� �� Y
    

    // �������������� ���������
    bool IsActive = true;               // ���������� �������
    bool IsVisible = true;              // ��������� �������
    bool IsCollidable = true;           // ����� �� ������ ������������
    bool IsStatic = false;              // �������� �� ������ ���������

    // �������������� ��������
    float PushForce = 1.0f;             // ���� ������������
    float Mass = 10.0f;                 // ����� �������

    // ��������
    Animation* animation = nullptr;     // ��������� �� ��������
    int SpriteRow = 0;                  // ����� ������ ��������

    // ����������� � ����������
    GameObject();
    virtual ~GameObject();

    // ���������� ��������� �������
    virtual void Update(float deltaTime);

    // ��������� ������������
    virtual void OnTriggerEnter(GameObject* object);

    // �������� ��� ��������������
    virtual void Action(GameObject* object);

    // ��������� �������
    void Draw(SDL_Renderer* renderer, const Camera& camera);

    // ����� ��� �������� ������������
    void ResolveCollision(GameObject* other);

    // ������ ��� ������ � �����������
    void UpdateCollider(); // ��������� ������� ����������
    bool CheckCollision(const GameObject& other) const; // ��������� ������������ � ������ ��������
};

#endif // GAMEOBJECT_H