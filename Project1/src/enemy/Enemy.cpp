#include "Enemy.h"


namespace
{
	const float FLASH_DURATION = 0.1f; // seconds
}

Enemy::Enemy()
	: mPosition(0.0f, 0.0f)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mIsActive(true)
	, mIsHit(false)
	, mTargetPlayer(nullptr)
{
	mRect = {0, 0, 0, 0};
	mFlashTime = FLASH_DURATION;
	mElapsedTime = mFlashTime;

	mEnemyType = ENEMY_TYPE_ENEMY;
	mEnemyName = "";
}



void Enemy::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = static_cast<float>(screenWidth);
	mPosition.y = static_cast<float>(rand() % (screenHeight - status.height));
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);

	InitializeBulletSpawnList(); // ’Ç‰Á
}

void Enemy::InitializeBulletSpawnList()
{
	mBulletSpawnList.clear(); // Šî’ê“G‚Í’e‚ðŒ‚‚½‚È‚¢
}

void Enemy::OnHit()
{
	if (mIsHit) return;
	mIsHit = true;
}

void Enemy::Update(float deltaTime)
{
	mPosition.x -= status.speed * deltaTime;
	mRect.x = static_cast<int>(mPosition.x);
	ClampPos();

	if (mIsHit)
	{
		mElapsedTime -= deltaTime;
		if(mElapsedTime <= 0.0f)
		{
			mIsHit = false;
			mElapsedTime = mFlashTime;
		}
	}
}

void Enemy::Render(SDL_Renderer* renderer)
{
	if (!mIsActive) return;
	if (mIsHit)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		mIsHit = false; 
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
	}
	SDL_RenderFillRect(renderer, &mRect);
}

void Enemy::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void Enemy::ClampPos()
{
	if (mPosition.y < 0.0f)
	{
		mPosition.y = 0.0f;
	}
	else if (mPosition.y + mRect.h > static_cast<float>(mScreenHeight))
	{
		mPosition.y = static_cast<float>(mScreenHeight) - mRect.h;
	}
	
	if(mPosition.x + mRect.w > static_cast<float>(mScreenWidth))
	{
		mPosition.x = static_cast<float>(mScreenWidth) - mRect.w;
	}
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}
