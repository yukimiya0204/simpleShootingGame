#pragma once	

#include "../Enemy.h"

class ShooterEnemy : public Enemy {
public:
	ShooterEnemy();

	virtual void Initialize(int screenWidth, int screenHeight) override;
	void Update(float deltaTime) override;
	virtual void Render(SDL_Renderer* renderer) override;
	virtual void InitializeBulletSpawnList() override; // ’Ç‰Á

protected:
	bool mIsUp;
};