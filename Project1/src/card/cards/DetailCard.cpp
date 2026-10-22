#include "DetailCard.h"

namespace
{
	const int CARD_WIDTH = 160;
	const int CARD_HEIGHT = 185;
}

DetailCard::DetailCard()
{
	mRect.w = CARD_WIDTH;
	mRect.h = CARD_HEIGHT;
}

DetailCard::~DetailCard()
{
}

void DetailCard::Initialize(int PosX, int PosY)
{
	Card::Initialize(PosX, PosY);
}

void DetailCard::Update(float deltaTime)
{
	//don't need to update
}

void DetailCard::Render(SDL_Renderer* renderer)
{
	if (mCardTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}
