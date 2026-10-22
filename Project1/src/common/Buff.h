#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Type.h"
#include "../bullet/Bullet.h"
class Player;


class Buff {
public:
	Buff();

	void applyBuff(BUFF_TYPE buffType, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList);
	void addBuff(BuffEntry& buff, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList);
	SDL_Texture* getBuffTexture(BUFF_TYPE buffType, TTF_Font* font, SDL_Renderer* renderer, SDL_Rect& rect, Player* player);
	SDL_Texture* getBuffImageTexture(BUFF_TYPE buffType, SDL_Renderer* renderer);
	BUFF_TYPE getRandomBuff(Player* player) const;
	

protected:
	bool isBullet(BUFF_TYPE buffType) const;
	BuffEntry* hasBuff(BUFF_TYPE buffType, const std::vector<BuffEntry>& buffList) const;
	const BuffTable* getBuffTable(BUFF_TYPE buffType) const;

	inline float getSpeedBuffValue(int count) const { return speedBuffValueTable[count - 1]; }
	inline float getPowerBuffValue(int count) const { return powerBuffValueTable[count - 1]; }
	inline float getDefenseBuffValue(int count) const { return defenseBuffValueTable[count - 1]; }
	float getBuffValue(BUFF_TYPE buffType, int count) const;
	int getBuffCount(BUFF_TYPE buffType, Player* player) const;
	size_t getMaxBuffCount(BUFF_TYPE buffType) const;

	
	std::string getBuffText(BUFF_TYPE buffType, int count);

	void applyBullet(BUFF_TYPE buffType, Player& player);

	void applyBuffEffect(BuffEntry& buff, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList);
	void removeBuffEffect(BuffEntry& buff, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList);
	void applyBuffEffectForBullet(BuffEntry& buff, std::vector<std::unique_ptr<Bullet>>& bulletList);
	void removeBuffEffectForBullet(BuffEntry& buff, std::vector<std::unique_ptr<Bullet>>& bulletList);
	bool isMaxBuffCount(int count, int maxCount) const;

	//-------------------------------------------
	// Buff value tables for different buff types
	//-------------------------------------------
	std::vector<float> speedBuffValueTable = {50.0f, 100.0f, 150.0f, 200.0f, 300.0f, 1.0f }; // Example values for speed buffs
	std::vector<float> powerBuffValueTable = { 50.0f, 100.0f, 150.0f, 200.0f, 300.0f, 1.0f }; // Example values for power buffs
	std::vector<float> defenseBuffValueTable = { 50.0f, 100.0f, 150.0f, 200.0f, 300.0f, 1.0f }; // Example values for defense buffs
	std::vector<float> bulletSpeedBuffValueTable = { 50.0f, 100.0f, 150.0f, 200.0f, 300.0f, 1.0f }; // Example values for bullet speed buffs
	std::vector<float> bulletPowerBuffValueTable = { 50.0f, 100.0f, 150.0f, 200.0f, 300.0f, 1.0f }; // Example values for bullet power buffs
	// More buff can be added here as needed
	std::vector<BuffTable> buffTable = {
		{ BUFF_TYPE_SPEED, false },
		{ BUFF_TYPE_POWER, false },
		{ BUFF_TYPE_DEFENSE, false },
		{ BUFF_TYPE_BULLET_POWER, false },
		{ BUFF_TYPE_BULLET_SPEED, false },
		{ BUFF_TYPE_BULLET_STRAIGHT, false },
		{ BUFF_TYPE_BULLET_BOTTOMLEFT, false },
		{ BUFF_TYPE_BULLET_TOPRIGHT, false },
		{ BUFF_TYPE_NONE, false },
		{ BUFF_TYPE_MAX, true }
	};


};