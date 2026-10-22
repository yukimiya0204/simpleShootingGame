#include "E_SinBullet.h"
#include "../../../loader/loaders/BulletLoader.h"	

E_SinBullet::E_SinBullet()
{
	status = BulletLoader::loadEnemyBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

E_SinBullet::~E_SinBullet()
{
}

void E_SinBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
	int enemyWidth, int enemyHeight)
{
	mTexture = texture;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = enemyPosX ;  // Start at enemy's position
	mPosition.y = enemyPosY + enemyHeight / 2; // Start at the middle of the enemy
	mStartX = mPosition.x;
	mStartY = mPosition.y;
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void E_SinBullet::Update(float deltaTime)
{
	mPosition.x -= status.speed * deltaTime;
	
	//”­ŽËˆÊ’u‚©‚ç‚ÌˆÚ“®‹——£‚ðŒvŽZ
	travelDistance = mStartX - mPosition.x;
	
	angle = (travelDistance / mScreenWidth) * (2.0f * M_PI);
	mPosition.y = static_cast<float>(mStartY + sin(angle) * amplitude);

	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void E_SinBullet::Render(SDL_Renderer* renderer)
{
	SinBullet::Render(renderer);
}