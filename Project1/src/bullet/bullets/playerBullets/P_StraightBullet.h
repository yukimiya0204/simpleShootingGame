#pragma once

#include "../bulletsType/StraightBullet.h"

class P_StraightBullet : public StraightBullet {
public:
	P_StraightBullet();
	~P_StraightBullet();
	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};