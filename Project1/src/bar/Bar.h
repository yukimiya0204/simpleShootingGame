#pragma once

#include <SDL2/SDL.h>

class Bar {
public:
	Bar();
	~Bar();
	void Initialize(int screenWidth, int screenHeight, int barWidth, int barHeight);
	void Update(float num, float maxNum);
	void Render(SDL_Renderer* renderer);
	inline void SetBarTexture(SDL_Texture* texture) { mBarTexture = texture; }

protected:
	SDL_Rect mRect;
	SDL_Texture* mBarTexture;

	int mMaxBarWidth;
};