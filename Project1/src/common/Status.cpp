#include "Status.h"

Status Status_Init() {
	Status status;

	status.width = 0;
	status.height = 0;

	status.baseHp = 0.0f;
	status.baseSpeed = 0.0f;
	status.power = 0.0f;
	status.baseHitAttack = 0.0f;
	status.baseDefense = 0.0f;
	status.knockbackDistance = 0.0f;

	status.maxHealth = status.baseHp;
	status.health = status.maxHealth;
	status.speed = status.baseSpeed;
	status.power = status.basePower;
	status.defense = status.baseDefense;
	
	return status;
}



