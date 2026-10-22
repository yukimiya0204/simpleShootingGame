#include "IconCard.h"

namespace {
	const int CARD_WIDTH = 100;
	const int CARD_HEIGHT = 100;
}

IconCard::IconCard()
{
	mRect.w = CARD_WIDTH;
	mRect.h = CARD_HEIGHT;
}

IconCard::~IconCard()
{
}

void IconCard::Initialize(int PosX, int PosY)
{
	Card::Initialize(PosX, PosY);
}

void IconCard::Update(float deltaTime)
{
	//don't need to update
}

void IconCard::Render(SDL_Renderer* renderer)
{
	if (mCardTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}