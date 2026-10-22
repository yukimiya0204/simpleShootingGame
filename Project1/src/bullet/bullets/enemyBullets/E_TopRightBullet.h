#pragma once

#include "../bulletsType/TopRightBullet.h"

class E_TopRightBullet : public TopRightBullet {
public: 
	E_TopRightBullet();
	~E_TopRightBullet();
	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
		int enemyWidth, int enemyHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};