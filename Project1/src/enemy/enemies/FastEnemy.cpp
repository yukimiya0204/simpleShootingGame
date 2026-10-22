#include "FastEnemy.h"
#include "../../loader/loaders/CharacterLoader.h"

FastEnemy::FastEnemy()
{
	mEnemyName = "FastEnemy";
	mEnemyType = ENEMY_TYPE_FASTENEMY;
	status = CharacterLoader::loadEnemyStatus(mEnemyName);
	mRect.w = status.width;
	mRect.h = status.height;
}

void FastEnemy::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mPosition.x = static_cast<float>(screenWidth);
	mPosition.y = static_cast<float>(rand() % (screenHeight - mRect.h));
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void FastEnemy::Update(float deltaTime)
{
	mPosition.x -= status.speed * deltaTime;
	mRect.x = static_cast<int>(mPosition.x);
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

void FastEnemy::Render(SDL_Renderer* renderer)
{
	if (mIsHit)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
	}
	SDL_RenderFillRect(renderer, &mRect);
}
