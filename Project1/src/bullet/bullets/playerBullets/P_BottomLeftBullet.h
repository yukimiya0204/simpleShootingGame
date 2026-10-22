#pragma once

#include "../bulletsType/BottomLeftBullet.h"

class P_BottomLeftBullet : public BottomLeftBullet {
public: 
	P_BottomLeftBullet();
	~P_BottomLeftBullet();

	void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};