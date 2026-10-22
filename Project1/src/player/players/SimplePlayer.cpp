#include "SimplePlayer.h"
#include "../../loader/loaders/CharacterLoader.h"




SimplePlayer::SimplePlayer() : Player() 
{
	{
		mPlayerName = "SimplePlayer";
		status = CharacterLoader::loadCharacterStatus(mPlayerName);
		mRect.w = status.width;
		mRect.h = status.height;

	}
}

SimplePlayer::~SimplePlayer() {
}

void SimplePlayer::Initialize(int screenWidth, int screenHeight) 
{
	Player::Initialize(screenWidth, screenHeight);
}

void SimplePlayer::InitializeBulletSpawnList() 
{
	mBulletSpawnList.clear();
	mBulletSpawnList.push_back({ BULLET_TYPE_PLAYER_STRAIGHT, 0.10f, 0.0f });
}

void SimplePlayer::ProcessInput(const Uint8* keyState) 
{
	Player::ProcessInput(keyState);
}

void SimplePlayer::Update(float deltaTime) 
{
	Player::Update(deltaTime);
}

void SimplePlayer::Render(SDL_Renderer* renderer) 
{
	if (!mIsActive) return;

	if (mPlayerTexture && !mIsHit) {
		SDL_RenderCopy(renderer, mPlayerTexture, nullptr, &mRect);
	}
	else if (mIsHit)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
		mIsHit = false; // Reset hit status after rendering
		SDL_RenderFillRect(renderer, &mRect);
	}
}
