#include "P_BottomLeftBullet.h"
#include "../../../loader/loaders/BulletLoader.h"	

P_BottomLeftBullet::P_BottomLeftBullet()
{
	status = BulletLoader::loadPlayerBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

P_BottomLeftBullet::~P_BottomLeftBullet()
{
}

void P_BottomLeftBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
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

void P_BottomLeftBullet::Update(float deltaTime)
{
	mPosition.x += static_cast<float>(status.speed * deltaTime * cos(deg2rad(status.angle))); // Move right
	mPosition.y += static_cast<float>(status.speed * deltaTime * sin(deg2rad(status.angle))); // Move down
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void P_BottomLeftBullet::Render(SDL_Renderer* renderer)
{
	BottomLeftBullet::Render(renderer);
}
