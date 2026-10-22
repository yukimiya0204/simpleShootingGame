#pragma once

#include "../common/Type.h"

struct BulletSpawnData {
	BULLET_TYPE bulletType; // 弾の種類
	float spawnInterval; // 弾の出現・u
	float currentSpawnTimer; // 現在の出現タイマー
};