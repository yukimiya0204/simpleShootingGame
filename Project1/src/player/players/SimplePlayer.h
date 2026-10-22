#pragma once

#include "../Player.h"

class SimplePlayer : public Player {
public:
	SimplePlayer();
	~SimplePlayer();

	void Initialize(int screenWidth, int screenHeight) override;
	void InitializeBulletSpawnList() override;
	void ProcessInput(const Uint8* keyState) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:

};