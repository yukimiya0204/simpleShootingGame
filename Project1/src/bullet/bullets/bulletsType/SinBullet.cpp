#include "SinBullet.h"



SinBullet::SinBullet()
{
	name = "SinBullet";
	angle = 0.0;
	mStartX = 0.0;
	mStartY = 0.0;
	travelDistance = 0.0;
	amplitude = 50.0f;
}

SinBullet::~SinBullet()
{
}

void SinBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
	int playerWidth, int playerHeight)
{
	mTexture = texture;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = playerPosX + playerWidth;  // Start at player's position
	mPosition.y = playerPosY + playerHeight / 2; // Start at the middle of the player
	mStartY = mPosition.y;
	mRect.x = static_cast<int>(mPosition.x);  
	mRect.y = static_cast<int>(mPosition.y); 

}

void SinBullet::Update(float deltaTime)
{
	mPosition.x += status.speed * deltaTime;
	//”­ŽËˆÊ’u‚©‚ç‚ÌˆÚ“®‹——£‚ðŒvŽZ
	travelDistance = mPosition.x - mStartX; 
	angle = static_cast<float>((travelDistance / mScreenWidth) * (2.0f * M_PI));// 2ƒÎ‚ÌŽüŠú‚Åsin”g‚ð•`‚­‚½‚ß‚ÌŠp“xŒvŽZ
	mPosition.y = mStartY + static_cast<float>(sin(angle)) * amplitude;

	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void SinBullet::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, mTexture, NULL, &mRect, angle, NULL, SDL_FLIP_NONE);
}