#include "PlayerSelectCard.h"

PlayerSelectCard::PlayerSelectCard()
{
	mRect.w = 200; // Set the width of the player select card
	mRect.h = 100; // Set the height of the player select card
}

PlayerSelectCard::~PlayerSelectCard()
{
}

void PlayerSelectCard::Initialize(int PosX, int PosY)
{
	mRect.x = PosX;
	mRect.y = PosY;
}

void PlayerSelectCard::Update(float deltaTime)
{
	//don't need to update
}

void PlayerSelectCard::Render(SDL_Renderer* renderer)
{
	// Render the player select card
	if (mCardTexture) {
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}




