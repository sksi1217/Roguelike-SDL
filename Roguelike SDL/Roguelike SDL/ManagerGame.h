#pragma once
#include "GameObject.h"
#include <vector> // ��� �������� ��������

class ManagerGame {
public:
    // ������ ���� �������� � ������������
    static std::vector<GameObject*> gameObjects;

    // ����� ��� ���������� ������� � ������
    static void AddGameObject(GameObject* obj);

    // ����� ��� ������� ������ ��������
    static void ClearGameObjects();
};