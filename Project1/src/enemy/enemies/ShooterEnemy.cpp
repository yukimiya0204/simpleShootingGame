#include <ctime>

#include "ShooterEnemy.h"
#include "../../bullet/bullets/enemyBullets/E_StraightBullet.h"
#include "../../loader/loaders/CharacterLoader.h"


ShooterEnemy::ShooterEnemy()
{
	mEnemyName = "ShooterEnemy";
	mEnemyType = ENEMY_TYPE_SHOOTERENEMY;
	status = CharacterLoader::loadEnemyStatus(mEnemyName);
	mRect.w = status.width;
	mRect.h = status.height;
	mIsUp = (rand() % 2 == 0); 
}



void ShooterEnemy::Initialize(int screenWidth, int screenHeight)
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

void ShooterEnemy::InitializeBulletSpawnList()
{
	mBulletSpawnList.clear();
	mBulletSpawnList.push_back({ BULLET_TYPE_ENEMY_STRAIGHT, 1.0f, 0.0f});
}
void ShooterEnemy::Update(float deltaTime)
{
	if (mIsUp)
	{
		mPosition.y += status.speed * deltaTime;
	}
	else
	{
		mPosition.y -= status.speed * deltaTime;
	}
	mRect.y = static_cast<int>(mPosition.y);

	if (mPosition.y >= mScreenHeight - mRect.h || mPosition.y <= 0)
	{
		mIsUp = !mIsUp;
	}
	ClampPos();

	if (mIsHit)
	{
		mElapsedTime -= deltaTime;
		if (mElapsedTime <= 0.0f)
		{
			mIsHit = false;
			mElapsedTime = mFlashTime;
		}
	}
}

void ShooterEnemy::Render(SDL_Renderer* renderer)
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
		SDL_SetRenderDrawColor(renderer, 0, 255, 100, 255);
	}

	SDL_RenderFillRect(renderer, &mRect);
}
