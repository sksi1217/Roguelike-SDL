#include "ManagerGame.h"

// Definition of static term
std::vector<GameObject*> ManagerGame::gameObjects;

// Method for adding an object to the list
void ManagerGame::AddGameObject(GameObject* obj) {
    if (obj != nullptr) {
        gameObjects.push_back(obj);
    }
}

// Method for clearing the list of objects
void ManagerGame::ClearGameObjects() {
    for (auto obj : gameObjects) {
        delete obj;
    }
    gameObjects.clear();
}