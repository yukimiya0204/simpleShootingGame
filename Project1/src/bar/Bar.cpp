#include "Bar.h"

Bar::Bar()
	: mBarTexture(nullptr)
	, mMaxBarWidth(0)
{
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = 0;
	mRect.h = 0;
}

Bar::~Bar()
{
	if (mBarTexture != nullptr)
	{
		SDL_DestroyTexture(mBarTexture);
		mBarTexture = nullptr;
	}
}

void Bar::Initialize(int screenWidth, int screenHeight, int barWidth, int barHeight){

	SetBarTexture(nullptr);
}

void Bar::Update(float num, float maxNum)
{
	mRect.w = static_cast<int>((num / maxNum) * mMaxBarWidth);
}

void Bar::Render(SDL_Renderer* renderer)
{
	if (mBarTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mBarTexture, NULL, &mRect);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
		SDL_RenderFillRect(renderer, &mRect);
	}
}