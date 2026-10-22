#pragma once


#include "../../Bullet.h"

class TopRightBullet : public Bullet {
public:

	TopRightBullet();
	~TopRightBullet();

	virtual void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(SDL_Renderer* renderer) override;

protected:
	bool mIsRotated;

	float mAngle;

};