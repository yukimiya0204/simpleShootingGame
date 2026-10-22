#pragma once

#include "../Card.h"

class IconCard : public Card {
public :

	IconCard();
	~IconCard();
	void Initialize(int PosX, int PosY) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};