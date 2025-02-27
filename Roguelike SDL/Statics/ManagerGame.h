#pragma once
#ifndef MANAGERGAME_H
#define MANAGERGAME_H

#include "../Abstracts/GameObject.h"
#include <vector>
#include <memory>

class ManagerGame {
public:
    static std::vector<std::unique_ptr<GameObject>> gameObjects;
    static std::vector<std::unique_ptr<GameObject>> enemies;

    static void AddGameObject(std::unique_ptr<GameObject> obj);
    static void Clear();
};

#endif // MANAGERGAME_H