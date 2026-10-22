#include "P_SinBullet.h"
#include "../../../loader/loaders/BulletLoader.h"

P_SinBullet::P_SinBullet()
{
	status = BulletLoader::loadPlayerBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

P_SinBullet::~P_SinBullet()
{
}

void P_SinBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
	int playerWidth, int playerHeight)
{
	SinBullet::Initialize(texture, screenWidth, screenHeight, playerPosX, playerPosY, playerWidth, playerHeight);
}

void P_SinBullet::Update(float deltaTime)
{
	SinBullet::Update(deltaTime);
}

void P_SinBullet::Render(SDL_Renderer* renderer)
{
	SinBullet::Render(renderer);
}