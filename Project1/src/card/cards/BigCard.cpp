#include "BigCard.h"

namespace 
{
	const int CARD_WIDTH = 190;
	const int CARD_HEIGHT = 350;
}

BigCard::BigCard()
{
	mRect.w = CARD_WIDTH;
	mRect.h = CARD_HEIGHT;
}

BigCard::~BigCard()
{
}

void BigCard::Initialize( int PosX, int PosY)
{
	Card::Initialize(PosX, PosY);
}

void BigCard::Update(float deltaTime)
{
	//don't need to update
}

void BigCard::Render(SDL_Renderer* renderer)
{
	if (mCardTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}

