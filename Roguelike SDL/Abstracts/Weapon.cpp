#include "Weapon.h"

// Метод для расчета урона
float Weapon::CalculateDamage() {
    float totalDamage = Damage;
    if (IsCriticalHit()) {
        totalDamage *= CriticalMultiplier;
    }
    return totalDamage;
}

GameObject* Weapon::FindNearestEnemy() {
    GameObject* nearestEnemy = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    for (const auto& obj : ManagerGame::enemies) {
        if (!obj || !obj->IsActive) continue; // Проверяем, что obj не null

        GameObject* enemy = obj.get(); // Получаем сырой указатель
        float distance = Help::Distance(StartPosition, enemy->Position);

        if (distance < Range && distance < minDistance) {
            minDistance = distance;
            nearestEnemy = enemy;
        }
    }

    return nearestEnemy;
}