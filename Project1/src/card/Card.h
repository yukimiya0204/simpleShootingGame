#pragma once

#include <SDL2/SDL.h>



class Card {
public:
	Card();
	~Card();
	static int mScreenWidth;
	static int mScreenHeight;

	static SDL_Texture* CreateRectBorderTexture(SDL_Renderer* renderer,SDL_Rect rect, int borderWidth, SDL_Color borderColor);

	virtual void Initialize(int PosX, int PosY);
	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);
	void SetCardTexture(SDL_Texture* texture);

	inline void SetRect(int x, int y, int w, int h) { mRect.x = x; mRect.y = y; mRect.w = w; mRect.h = h; }
	inline SDL_Rect GetRect() const { return mRect; }
protected:
	SDL_Rect mRect;
	SDL_Texture* mCardTexture;
};

