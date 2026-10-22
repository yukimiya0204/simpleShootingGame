#pragma once

#include "../Card.h"

class DetailCard : public Card {
public:
	DetailCard();
	~DetailCard();
	void Initialize(int PosX, int PosY) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};