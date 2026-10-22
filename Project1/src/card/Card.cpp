#include "Card.h"

int Card::mScreenWidth;
int Card::mScreenHeight;

Card::Card()
	: mCardTexture(nullptr)
{
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = 0;
	mRect.h = 0;
}

Card::~Card()
{
}

SDL_Texture* Card::CreateRectBorderTexture(SDL_Renderer* renderer, SDL_Rect rect, int borderWidth, SDL_Color borderColor)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, rect.w, rect.h, 32, SDL_PIXELFORMAT_RGBA32);
	if (surface == nullptr)
	{
		SDL_Log("Failed to create surface: %s", SDL_GetError());
		return nullptr;
	}

	Uint32 color = SDL_MapRGBA(surface->format, borderColor.r, borderColor.g, borderColor.b, borderColor.a);

	//draw the border
	SDL_Rect topRect = { 0, 0, rect.w, borderWidth };							// Top border
	SDL_Rect bottomRect = { 0, rect.h - borderWidth, rect.w, borderWidth };		// Bottom border
	SDL_Rect leftRect = { 0, 0, borderWidth, rect.h };							// Left border
	SDL_Rect rightRect = { rect.w - borderWidth, 0, borderWidth, rect.h };		// Right border

	SDL_FillRect(surface, &topRect, color);
	SDL_FillRect(surface, &bottomRect, color);
	SDL_FillRect(surface, &leftRect, color);
	SDL_FillRect(surface, &rightRect, color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}

void Card::Initialize( int PosX, int PosY)
{
	mRect.x = PosX;
	mRect.y = PosY;
}


void Card::Update(float deltaTime)
{
}

void Card::SetCardTexture(SDL_Texture* texture)
{
	mCardTexture = texture;
}

void Card::Render(SDL_Renderer* renderer)
{
	if (mCardTexture != nullptr)
	{
		SDL_RenderCopy(renderer, mCardTexture, nullptr, &mRect);
	}
}