#include "calc.h"


float Calc::CalcDamage(const Status& attackerStatus, const Status& targetStatus, const BulletStatus& bulletStatus, const LEVEL_NUMBER level)
{
	float DefenseRate = CalcDefenseRate(targetStatus.defense, level);
	float totalDamage = (attackerStatus	.power + bulletStatus.power) * DefenseRate;
	return totalDamage;
}

float Calc::CalcDefenseRate(const float targetDefense, const LEVEL_NUMBER level)
{
	float defenseRate = targetDefense / (targetDefense + (10 * level)); 
	return defenseRate;
}
