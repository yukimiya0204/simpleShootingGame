#include "E_StraightBullet.h"
#include "../../../loader/loaders/BulletLoader.h"	

E_StraightBullet::E_StraightBullet()
{
	status = BulletLoader::loadEnemyBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

E_StraightBullet::~E_StraightBullet()
{
}

void E_StraightBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
	int enemyWidth, int enemyHeight)
{
	mTexture = texture;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = enemyPosX ; // Start at enemy's position
	mPosition.y = enemyPosY + enemyHeight / 2; // Start at the middle of the enemy
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void E_StraightBullet::Update(float deltaTime)
{
	mPosition.x -= status.speed * deltaTime; // Move left
	mRect.x = static_cast<int>(mPosition.x);
}

void E_StraightBullet::Render(SDL_Renderer* renderer)
{
	StraightBullet::Render(renderer);
}