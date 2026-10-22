#include "P_StraightBullet.h"
#include "../../../loader/loaders/BulletLoader.h"

P_StraightBullet::P_StraightBullet()
{
	status = BulletLoader::loadPlayerBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

P_StraightBullet::~P_StraightBullet()
{
}

void P_StraightBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
	int playerWidth, int playerHeight)
{
	StraightBullet::Initialize(texture, screenWidth, screenHeight, playerPosX, playerPosY, playerWidth, playerHeight);
}

void P_StraightBullet::Update(float deltaTime)
{
	StraightBullet::Update(deltaTime);
}

void P_StraightBullet::Render(SDL_Renderer* renderer)
{
	StraightBullet::Render(renderer);
}

