#pragma once

#include "../Status.h"
#include "../../bullet/BulletStatus.h"
#include "../LevelTable.h"

class Calc {
public:

	float CalcDamage(const Status& attackerStatus, const Status& targetStatus, const BulletStatus& bulletStatus, const LEVEL_NUMBER level);
	float CalcDefenseRate(const float targetDefense, const LEVEL_NUMBER level);
};