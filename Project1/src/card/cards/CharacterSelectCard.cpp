#include "CharacterSelectCard.h"

CharacterSelectCard::CharacterSelectCard()
{
	mRect.w = 200; // Set the width of the character select card
	mRect.h = 100; // Set the height of the character select card
}

CharacterSelectCard::~CharacterSelectCard()
{
}

void CharacterSelectCard::Initialize(int PosX, int PosY)
{
	Card::Initialize(PosX, PosY);
}

void CharacterSelectCard::Update(float deltaTime)
{
	//don't need to update
}

void CharacterSelectCard::Render(SDL_Renderer* renderer)
{
	if (mCardTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}