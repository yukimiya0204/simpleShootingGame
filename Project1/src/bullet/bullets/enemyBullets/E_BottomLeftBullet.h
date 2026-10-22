#pragma once

#include "../bulletsType/BottomLeftBullet.h"

class E_BottomLeftBullet : public BottomLeftBullet {
public:
	E_BottomLeftBullet();
	~E_BottomLeftBullet();
	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
		int enemyWidth, int enemyHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};