#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <cstdint>

class Animation {
public:
    // Size of one sprite
    int FrameWidth;
    int FrameHeight;

    int CurrentFrame;
    int TotalFrames; 
    float TimePerFrame; // Time between frames (in seconds)
    float ElapsedTime;

    // Flag to determine if the object is moving
    bool IsPlaying;

    // Designer
    Animation(int frameWidth, int frameHeight, int totalFrames, float timePerFrame);

    // Animation update
    void Update(bool isMoving, Uint32 deltaTime);

    // Getting the rectangle of the current frame
    SDL_Rect GetCurrentFrameRectangle(int spriteRow) const;
};

#endif // ANIMATION_H