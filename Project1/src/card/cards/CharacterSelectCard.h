#pragma once

#include "../Card.h"

class CharacterSelectCard : public Card {
public:
	CharacterSelectCard();
	~CharacterSelectCard();
	void Initialize(int PosX, int PosY) override;
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* renderer) override;
private:
};