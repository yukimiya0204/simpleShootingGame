#pragma once

#include "../Card.h"

class BigCard : public Card {
public: 
	BigCard();
	~BigCard();
	void Initialize( int PosX, int PosY) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;

};