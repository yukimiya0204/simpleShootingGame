#include "BottomLeftBullet.h"


BottomLeftBullet::BottomLeftBullet()
	: mIsRotated(false)
{
	name = "BottomLeftBullet";
}

BottomLeftBullet::~BottomLeftBullet()
{
}	

void BottomLeftBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
	int playerWidth, int playerHeight)
{
	mTexture = texture;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = playerPosX + playerWidth;  // Start at player's position
	mPosition.y = playerPosY + playerHeight / 2; // Start at the bottom of the player
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);

	if (mTexture == nullptr)
	{

	}
	
}

void BottomLeftBullet::Update(float deltaTime)
{
	mPosition.x += status.speed * deltaTime * static_cast<float>(cos(deg2rad(status.angle))); // Move right
	mPosition.y += status.speed * deltaTime * static_cast<float>(sin(deg2rad(status.angle))); // Move down
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void BottomLeftBullet::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopyEx(renderer, mTexture, NULL, &mRect, status.angle, NULL, SDL_FLIP_NONE);
}



