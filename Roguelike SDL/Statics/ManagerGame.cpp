#include "ManagerGame.h"

// Определение статических членов
std::vector<std::unique_ptr<GameObject>> ManagerGame::gameObjects;
std::vector<std::unique_ptr<GameObject>> ManagerGame::enemies;

// Методы класса
void ManagerGame::AddGameObject(std::unique_ptr<GameObject> obj) {
    if (obj && obj->IsActive) {
        gameObjects.emplace_back(std::move(obj));
    }
}

void ManagerGame::Clear() {
    gameObjects.clear(); // Очищаем все объекты
    enemies.clear();     // Очищаем всех врагов
}