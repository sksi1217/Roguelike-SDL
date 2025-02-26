#pragma once
#include "../Abstracts/GameObject.h"
#include <vector>

class ManagerGame {
public:
    static std::vector<GameObject*> gameObjects;
    static std::vector<GameObject*> enemies;
};