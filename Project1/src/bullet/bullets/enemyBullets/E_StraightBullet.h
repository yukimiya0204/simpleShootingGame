#pragma once

#include "../bulletsType/StraightBullet.h"

class E_StraightBullet : public StraightBullet {
public:
	E_StraightBullet();
	~E_StraightBullet();
	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
		int enemyWidth, int enemyHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};