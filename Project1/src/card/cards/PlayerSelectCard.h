#pragma once

#include "../Card.h"

class PlayerSelectCard : public Card
{
public:
	PlayerSelectCard();
	~PlayerSelectCard();
	void Initialize(int PosX, int PosY) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};
