#pragma once


#include "../Bar.h"

class HpBar : public Bar {
public:
	HpBar();
	~HpBar();
	void Initialize(int screenWidth, int screenHeight, int barWidth, int barHeight);
	void Update(float num, float maxNum);
	void Render(SDL_Renderer* renderer);
	inline void SetBarTexture(SDL_Texture* texture) { mBarTexture = texture; }


};