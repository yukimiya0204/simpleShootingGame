#pragma once

#include "ShooterEnemy.h"

class SinShooterEnemy : public ShooterEnemy {
public :
	SinShooterEnemy();
	~SinShooterEnemy();
	void Initialize(int screenWidth, int screenHeight) override;
	void Render(SDL_Renderer* renderer) override;
	void InitializeBulletSpawnList() override; // ’Ç‰Á

};