#include "StraightBullet.h"


StraightBullet::StraightBullet()
{
	name = "StraightBullet";
}

StraightBullet::~StraightBullet()
{
}

void StraightBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
	int playerWidth, int playerHeight)
{
	mTexture = texture;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = playerPosX + playerWidth; // Start at player's position
	mPosition.y = playerPosY + playerHeight / 2; // Start at the middle of the player
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void StraightBullet::Update(float deltaTime)
{
	mPosition.x += status.speed * deltaTime; // Move right
	mRect.x = static_cast<int>(mPosition.x);
}

void StraightBullet::Render(SDL_Renderer* renderer)
{ 
	SDL_RenderCopy(renderer, mTexture, NULL, &mRect);
}	



