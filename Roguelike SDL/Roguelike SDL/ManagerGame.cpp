#include "ManagerGame.h"

// Определение статического члена
std::vector<GameObject*> ManagerGame::gameObjects;

// Метод для добавления объекта в список
void ManagerGame::AddGameObject(GameObject* obj) {
    if (obj != nullptr) {
        gameObjects.push_back(obj);
    }
}

// Метод для очистки списка объектов
void ManagerGame::ClearGameObjects() {
    for (auto obj : gameObjects) {
        delete obj; // Удаляем каждый объект
    }
    gameObjects.clear(); // Очищаем список
}