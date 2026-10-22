#include "Player.h"
#include "../loader/loaders/CharacterLoader.h"


namespace {
	const int PLAYER_FIXED_X = 50; 
	const float FLASH_DURATION = 2.0f; // seconds
}

Player::Player()
	: mPosX(0.0f)
	, mPosY(0.0f)
	, mScreenWidth(0)
	, mScreenHeight(0)
	, mMoveUp(false)
	, mMoveDown(false)
	, mMoveLeft(false)
	, mMoveRight(false)
	, mIsHit(false)
	, mIsActive(true)
	, mExp(0.0f)
	, mMaxExp(0.0f)
	, mPlayerTexture(nullptr)
	, mCurrentLevel(LEVEL_1)
{
	mRect = { PLAYER_FIXED_X, 0, 0, 0 };
	mFlashTime = FLASH_DURATION;
	mElapsedTime = mFlashTime;
	//status = Status_Init();
	
}

Player::~Player() 
{
	if (mPlayerTexture != nullptr)
	{
		SDL_DestroyTexture(mPlayerTexture);
		mPlayerTexture = nullptr;
	}
}



void Player::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
	mPosX = static_cast<float>(PLAYER_FIXED_X);
	mPosY = static_cast<float>(screenHeight) / 2.0f - mRect.h / 2.0f;
	mRect.x = static_cast<int>(mPosX);
	mRect.y = static_cast<int>(mPosY);


	InitializeBulletSpawnList();
	SetMaxExp(mCurrentLevel);
}

void Player::InitializeBulletSpawnList()
{
	mBulletSpawnList.clear();

	mBulletSpawnList.push_back({ BULLET_TYPE_PLAYER_STRAIGHT, 0.10f, 0.0f});
}

// move around by WASD keys
void Player::ProcessInput(const Uint8* keyState)
{
	mMoveUp = keyState[SDL_SCANCODE_W];
	mMoveDown = keyState[SDL_SCANCODE_S];
	mMoveLeft = keyState[SDL_SCANCODE_A];
	mMoveRight = keyState[SDL_SCANCODE_D];
}

void Player::Update(float deltaTime)
{
	if (mMoveUp)
	{
		mPosY -= status.speed * deltaTime;
	}
	if (mMoveDown)
	{
		mPosY += status.speed * deltaTime;
	}
	if (mMoveLeft)
	{
		mPosX -= status.speed * deltaTime;
	}
	if (mMoveRight)
	{
		mPosX += status.speed * deltaTime;
	}
	ClampPos();

	if (mIsHit) {
		mElapsedTime -= deltaTime;
		if (mElapsedTime <= 0.0f)
		{
			mIsHit = false;
			mElapsedTime = mFlashTime;
		}
	}
}

bool Player::isBulletTypeInSpawnList(BULLET_TYPE bulletType)
{
	for (const auto& spawnData : mBulletSpawnList)
	{
		if (spawnData.bulletType == bulletType)
		{
			return true;
		}
	}
	return false;
}

void Player::AddBulletSpawnData(BulletSpawnData spawnData)
{
	mBulletSpawnList.push_back(spawnData);
}

void Player::SetPosition(float x, float y)
{
	mPosX = x;
	mPosY = y;
	mRect.x = static_cast<int>(mPosX);
	mRect.y = static_cast<int>(mPosY);
}

// Clamp the player's position to stay within the screen
void Player::ClampPos()
{
	if (mPosY < 0.0f)
	{
		mPosY = 0.0f;
	}
	else if (mPosY + mRect.h > static_cast<float>(mScreenHeight))
	{
		mPosY = static_cast<float>(mScreenHeight) - mRect.h;
	}
	if(mPosX < 0.0f)
	{
		mPosX = 0.0f;
	}
	else if(mPosX + mRect.w > static_cast<float>(mScreenWidth))
	{
		mPosX = static_cast<float>(mScreenWidth) - mRect.w;
	}
	mRect.x = static_cast<int>(mPosX);
	mRect.y = static_cast<int>(mPosY);
}

void Player::Render(SDL_Renderer* renderer)
{

	if (mPlayerTexture && !mIsHit) {
		SDL_RenderCopy(renderer, mPlayerTexture, nullptr, &mRect);
	}
	else if(mIsHit)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
		mIsHit = false; // Reset hit status after rendering
		SDL_RenderFillRect(renderer, &mRect);
	}
	
}