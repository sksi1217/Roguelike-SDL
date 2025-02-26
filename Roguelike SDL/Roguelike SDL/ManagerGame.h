#pragma once
#include "GameObject.h"
#include <vector> // Для хранения объектов

class ManagerGame {
public:
    // Список всех объектов с коллайдерами
    static std::vector<GameObject*> gameObjects;

    // Метод для добавления объекта в список
    static void AddGameObject(GameObject* obj);

    // Метод для очистки списка объектов
    static void ClearGameObjects();
};