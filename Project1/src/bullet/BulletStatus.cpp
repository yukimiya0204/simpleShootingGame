#include "BulletStatus.h"

BulletStatus BulletStatus_Init()
{
	BulletStatus status;

	status.speed = 0.0f;
	status.power = 0.0f;
	status.width = 0;
	status.height = 0;
	status.angle = 0.0f;

	return status;
}

