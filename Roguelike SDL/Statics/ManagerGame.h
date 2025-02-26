#pragma once
#ifndef MANAGERGAME_H
#define MANAGERGAME_H


#include "../Abstracts/GameObject.h"
#include <vector>

class ManagerGame {
public:
    static std::vector<GameObject*> gameObjects;
    static std::vector<GameObject*> enemies;
};
#endif // MANAGERGAME_H