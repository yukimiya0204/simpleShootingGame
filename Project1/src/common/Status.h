#pragma once

#include <string>
#include "../common/Type.h"
#include "../common/LevelTable.h"

struct Status {
    int width = 0;                      // Width
    int height = 0;                     // Height

    float baseHp = 0.0f;                // Base health
    float baseSpeed = 0.0f;             // Base speed
    float basePower = 0.0f;             // Base attack power
    float baseHitAttack = 0.0f;         // Base physical attack power
    float baseDefense = 0.0f;           // Base defense
    float knockbackDistance = 0.0f;     // Knockback distance

    // Calculated status
    float maxHealth = 0.0f;             // Maximum health
    float health = 0.0f;                // Health
    float speed = 0.0f;                 // Speed
    float power = 0.0f;                 // Attack power
    float defense = 0.0f;               // Defense
};

struct EnemyStatus : public Status {
    float exp = 0.0f;                   // Experience
};



Status Status_Init();


