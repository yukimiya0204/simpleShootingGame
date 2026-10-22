#include "P_TopRightBullet.h"
#include "../../../loader/loaders/BulletLoader.h"

P_TopRightBullet::P_TopRightBullet()
{
	status = BulletLoader::loadPlayerBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

P_TopRightBullet::~P_TopRightBullet()
{
}

void P_TopRightBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
	int playerWidth, int playerHeight)
{
	TopRightBullet::Initialize(texture, screenWidth, screenHeight, playerPosX, playerPosY, playerWidth, playerHeight);
}

void P_TopRightBullet::Update(float deltaTime)
{
	TopRightBullet::Update(deltaTime);
}

void P_TopRightBullet::Render(SDL_Renderer* renderer)
{
	TopRightBullet::Render(renderer);
}