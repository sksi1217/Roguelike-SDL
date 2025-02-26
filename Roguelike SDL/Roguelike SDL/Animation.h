#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <cstdint>

class Animation {
public:
    // ������ ������ �������
    int FrameWidth;
    int FrameHeight;

    // ��������
    int CurrentFrame; // ������� ����
    int TotalFrames;  // ����� ���������� ������
    float TimePerFrame; // ����� ����� ������� (� ��������)
    float ElapsedTime;  // ��������� ����� ��� �������� �����

    // ���� ��� �����������, �������� �� ������
    bool IsPlaying;

    // �����������
    Animation(int frameWidth, int frameHeight, int totalFrames, float timePerFrame);

    // ���������� ��������
    void Update(bool isMoving, Uint32 deltaTime);

    // ��������� �������������� �������� �����
    SDL_Rect GetCurrentFrameRectangle(int spriteRow) const;
};

#endif // ANIMATION_H