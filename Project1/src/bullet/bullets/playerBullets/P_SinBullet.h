#pragma once

#include "../bulletsType/SinBullet.h"

class P_SinBullet : public SinBullet {
public:
	P_SinBullet();
	~P_SinBullet();

	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};