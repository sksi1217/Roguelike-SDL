#include "ManagerGame.h"

// ����������� ������������ �����
std::vector<GameObject*> ManagerGame::gameObjects;

// ����� ��� ���������� ������� � ������
void ManagerGame::AddGameObject(GameObject* obj) {
    if (obj != nullptr) {
        gameObjects.push_back(obj);
    }
}

// ����� ��� ������� ������ ��������
void ManagerGame::ClearGameObjects() {
    for (auto obj : gameObjects) {
        delete obj; // ������� ������ ������
    }
    gameObjects.clear(); // ������� ������
}