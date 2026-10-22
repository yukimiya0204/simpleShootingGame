#include "SpeedPlayer.h"
#include "../../loader/loaders/CharacterLoader.h"

SpeedPlayer::SpeedPlayer() : Player() {
	{
		mPlayerName = "SpeedPlayer";
		status = CharacterLoader::loadCharacterStatus(mPlayerName);
		mRect.w = status.width;
		mRect.h = status.height;
	}
}

SpeedPlayer::~SpeedPlayer() {
}

void SpeedPlayer::Initialize(int screenWidth, int screenHeight)
{
	Player::Initialize(screenWidth, screenHeight);
}

void SpeedPlayer::InitializeBulletSpawnList()
{
	mBulletSpawnList.clear();
	mBulletSpawnList.push_back({ BULLET_TYPE_PLAYER_STRAIGHT, 0.10f, 0.0f });
}

void SpeedPlayer::ProcessInput(const Uint8* keyState)
{
	Player::ProcessInput(keyState);
}

void SpeedPlayer::Update(float deltaTime)
{
	Player::Update(deltaTime);
}

void SpeedPlayer::Render(SDL_Renderer* renderer)
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
