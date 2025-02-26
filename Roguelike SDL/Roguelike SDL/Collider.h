#pragma once
#include <SDL.h>

class Collider {
public:
    SDL_Rect rect; // ��������� ��� �������������

    // �����������
    Collider(int x, int y, int w, int h);

    // ����� ��� ���������� ������� ����������
    void UpdatePosition(float objX, float objY, int offsetX, int offsetY);

    // �������� ������������ � ������ �����������
    bool CheckCollision(const Collider& other) const;

    // ����� ��� ���������� ������������
    void ResolveCollision(const Collider& other, float dx, float dy, float& objX, float& objY);
};