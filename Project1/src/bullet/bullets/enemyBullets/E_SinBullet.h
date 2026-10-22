#pragma once

#include "../bulletsType/SinBullet.h"

class E_SinBullet : public SinBullet {
public:
	E_SinBullet();
	~E_SinBullet();
	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
		int enemyWidth, int enemyHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};