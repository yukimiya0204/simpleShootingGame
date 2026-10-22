#include "E_BottomLeftBullet.h"
#include "../../../loader/loaders/BulletLoader.h"	

E_BottomLeftBullet::E_BottomLeftBullet()
{
	status = BulletLoader::loadEnemyBullet(name);
	mRect.w = status.width;
	mRect.h = status.height;
}

E_BottomLeftBullet::~E_BottomLeftBullet()
{
}

void E_BottomLeftBullet::Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float enemyPosX, float enemyPosY,
	int enemyWidth, int enemyHeight)
{
	mTexture = texture;
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = enemyPosX;  // Start at enemy's position
	mPosition.y = enemyPosY + enemyHeight / 2; // Start at the bottom of the enemy
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);

	if (mTexture == nullptr)
	{

	}
}

void E_BottomLeftBullet::Update(float deltaTime)
{
	mPosition.x -= static_cast<float>(status.speed * deltaTime * cos(deg2rad(status.angle))); // Move left
	mPosition.y += static_cast<float>(status.speed * deltaTime * sin(deg2rad(status.angle))); // Move down
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void E_BottomLeftBullet::Render(SDL_Renderer* renderer)
{
	BottomLeftBullet::Render(renderer);
}
