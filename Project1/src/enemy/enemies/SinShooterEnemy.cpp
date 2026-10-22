#include <ctime>

#include "SinShooterEnemy.h"
#include "../../bullet/bullets/enemyBullets/E_SinBullet.h"
#include "../../loader/loaders/CharacterLoader.h"




SinShooterEnemy::SinShooterEnemy()
{
	mEnemyName = "SinShooterEnemy";
	mEnemyType = ENEMY_TYPE_SINSHOOTERENEMY;
	status = CharacterLoader::loadEnemyStatus(mEnemyName);
	mRect.w = status.width;
	mRect.h = status.height;
}

SinShooterEnemy::~SinShooterEnemy()
{
}


void SinShooterEnemy::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	int minX = screenWidth / 2;
	int rangeX = minX - mRect.w;
	mPosition.x = static_cast<float>(minX + rand() % rangeX);

	int maxY = screenHeight - mRect.h;
	mPosition.y = static_cast<float>(rand() % maxY);

	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);

	InitializeBulletSpawnList(); // 追加
}

void SinShooterEnemy::InitializeBulletSpawnList()
{
	mBulletSpawnList.clear();
	mBulletSpawnList.push_back({ BULLET_TYPE_ENEMY_SIN, 1.0f, 0.0f});//この球を変更する 
}


void SinShooterEnemy::Render(SDL_Renderer* renderer)
{
	if (!mIsActive) return;

	if (mIsHit)
	{
		// 反対色: ローズピンク (255, 0, 155)
		SDL_SetRenderDrawColor(renderer, 255, 0, 155, 255);
	}
	else
	{
		// 通常色: (0, 255, 100)
		SDL_SetRenderDrawColor(renderer, 100, 0, 200, 255);
	}

	SDL_RenderFillRect(renderer, &mRect);
}
