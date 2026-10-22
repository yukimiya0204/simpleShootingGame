#pragma once

#include "../Card.h"

class MenuCard : public Card {
public:
	MenuCard();
	~MenuCard();
	void Initialize(int PosX, int PosY) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
};