#pragma once

#include "../bulletsType/TopRightBullet.h"

class P_TopRightBullet : public TopRightBullet {
public:
	P_TopRightBullet();
	~P_TopRightBullet();
	virtual void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(SDL_Renderer* renderer) override;
};