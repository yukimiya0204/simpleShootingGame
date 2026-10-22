#pragma once

#include <string>
#include <SDL2/SDL.h>

typedef struct {
	int width;			 // ’e‚Ì•
	int height;			 // ’e‚Ì‚‚³

	float speed;         // ’e‚Ì‘¬“x
	float power;         // ’e‚ÌˆĞ—Í

	float angle;		 // ’e‚ÌŠp“x
} BulletStatus;

BulletStatus BulletStatus_Init();