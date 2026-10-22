#pragma once

#include "../Enemy.h"

class FastEnemy : public Enemy {
public:
	FastEnemy();
	void Initialize(int screenWidth, int screenHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};