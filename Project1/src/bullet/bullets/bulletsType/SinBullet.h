#pragma once

#include "../../bullet.h"

class SinBullet : public Bullet {
public:

	SinBullet();
	~SinBullet();

	virtual void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) override;
	virtual void Update(float deltaTime) override;
	virtual void Render(SDL_Renderer* renderer) override;

protected:
	double angle;
	float  mStartX;
	float  mStartY;
	float travelDistance; //”­ËˆÊ’u‚©‚ç‚ÌˆÚ“®‹——£
	float amplitude;	  //U•
};