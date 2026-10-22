#include "ExpBar.h"

ExpBar::ExpBar()
{

}

ExpBar::~ExpBar()
{

}	 

void ExpBar::Initialize(int screenWidth, int screenHeight, int barWidth, int barHeight)
{
	mRect = { 500, 0, barWidth, barHeight };
	mMaxBarWidth = barWidth;
	SetBarTexture(nullptr);
}

void ExpBar::Update(float num, float maxNum)
{
	mRect.w = static_cast<int>((num / maxNum) * mMaxBarWidth);
}

void ExpBar::Render(SDL_Renderer* renderer)
{
	if (mBarTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mBarTexture, NULL, &mRect);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 200, 255, 200); // Blue color
		SDL_RenderFillRect(renderer, &mRect);
	}
}