
#include "FollowTargetEnemy.h"
#include "../../player/Player.h"
#include "../../loader/loaders/CharacterLoader.h"

FollowTargetEnemy::FollowTargetEnemy()
{
	mEnemyName = "FollowTargetEnemy";
	mEnemyType = ENEMY_TYPE_FOLLOWTARGETENEMY;
	status = CharacterLoader::loadEnemyStatus(mEnemyName);
	mRect.w = status.width;
	mRect.h = status.height;
}

void FollowTargetEnemy::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosition.x = static_cast<float>(screenWidth);
	mPosition.y = static_cast<float>(rand() % (screenHeight - mRect.h));
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
}

void FollowTargetEnemy::Update(float deltaTime)
{
	Vector2 directionToPlayer(mTargetPlayer->GetPosX(), mTargetPlayer->GetPosY());

	Vector2 direction = (directionToPlayer - mPosition).normalized();
	Vector2 movement = direction * status.speed * deltaTime;
	
	mPosition = mPosition + movement;
	
	mRect.x = static_cast<int>(mPosition.x);
	mRect.y = static_cast<int>(mPosition.y);
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

void FollowTargetEnemy::Render(SDL_Renderer* renderer)
{
	if (mIsHit)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange color
	}
	SDL_RenderFillRect(renderer, &mRect);
}