#include "MenuCard.h"

MenuCard::MenuCard()
{
	mRect.w = 200; // Set the width of the menu card
	mRect.h = 100; // Set the height of the menu card
}

MenuCard::~MenuCard()
{
}

void MenuCard::Initialize(int PosX, int PosY)
{
	Card::Initialize(PosX, PosY);
}

void MenuCard::Update(float deltaTime)
{
	//don't need to update
}

void MenuCard::Render(SDL_Renderer* renderer)
{
	if (mCardTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}


