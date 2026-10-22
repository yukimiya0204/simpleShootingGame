#pragma once

#include <string>
#include <vector>

#include "../common/Type.h"

// フェーズ内での1種類の敵の出現情報
struct EnemySpawnData {
    ENEMY_TYPE enemyType; // 敵の種類
    int count;             // あと何体出現させるか（残り出現数）
    float spawnInterval;   // この敵の出現間隔（秒）
    float currentSpawnTimer;                            // 現在の出現タイマー
};

// 1つのフェーズ情報
struct Phase {
    PHASE_NUMBER phaseNumber;                        // フェーズ番号
    std::vector<EnemySpawnData> spawnList;  // このフェーズで出現する敵のリスト
};  