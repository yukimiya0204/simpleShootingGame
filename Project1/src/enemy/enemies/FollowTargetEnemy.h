#pragma once

#include "../Enemy.h"

class FollowTargetEnemy : public Enemy {
public:
	FollowTargetEnemy();

	void Initialize(int screenWidth, int screenHeight) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;

};