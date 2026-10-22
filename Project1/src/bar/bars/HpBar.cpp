#include "HpBar.h"

HpBar::HpBar()
{

}

HpBar::~HpBar()
{

}

void HpBar::Initialize(int screenWidth, int screenHeight, int barWidth, int barHeight)
{
	mRect = { 500, 20, barWidth, barHeight };
	mMaxBarWidth = barWidth;
	SetBarTexture(nullptr);
}

void HpBar::Update(float num, float maxNum)
{
	mRect.w = static_cast<int>((num / maxNum) * mMaxBarWidth);
}

void HpBar::Render(SDL_Renderer* renderer)
{
	if (mBarTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mBarTexture, NULL, &mRect);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
		SDL_RenderFillRect(renderer, &mRect);
	}
}