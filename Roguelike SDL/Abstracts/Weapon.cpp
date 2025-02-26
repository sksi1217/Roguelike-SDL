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
        if (!obj->IsActive) continue;
        float distance = Help::Distance(Position, obj->Position);
        if (distance < Range && distance < minDistance) {
            minDistance = distance;
            nearestEnemy = obj;
        }
    }
    return nearestEnemy;
}