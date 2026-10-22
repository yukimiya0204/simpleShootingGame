#include <sstream>
#include <string>
#include <SDL2/SDL_image.h>


#include "Buff.h"

#include "../player/Player.h"
#include "../loader/Loader.h"

Buff::Buff() 
{
}

//apply buff to player. 
// if the buff already exists, increase the count and update the buff value. 
void Buff::applyBuff(BUFF_TYPE buffType, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList) {
	if (isBullet(buffType))
	{
		applyBullet(buffType, *player);
		auto it = std::find_if(buffTable.begin(), buffTable.end(), [buffType](const BuffTable& b)
			{
				return b.buffType == buffType;
			});
		if (it != buffTable.end() && !it->isMaxCount)
		{
			it->isMaxCount = true;
		}
		return;
	}
	
	BuffEntry* buff = hasBuff(buffType, player->mBuffList);
	if (buff == nullptr) {
		BuffEntry Buff;
		Buff.buffType = buffType;
		Buff.count = 1;
		Buff.buffValue = getBuffValue(buffType, Buff.count);
		Buff.maxCount =  getMaxBuffCount(buffType);
		addBuff(Buff, player, bulletList);
	}
	else
	{
		if(buff->count >= buff->maxCount)
		{
			auto it = std::find_if(buffTable.begin(), buffTable.end(), [buffType](const BuffTable& b) 
				{
				return b.buffType == buffType;
				});
			if (it != buffTable.end() && !it -> isMaxCount)
			{
				it->isMaxCount = true;
			}
			return;
		}
		removeBuffEffect(*buff, player, bulletList);
		buff->count++;
		buff->buffValue = getBuffValue(buffType, buff->count);
		applyBuffEffect(*buff, player, bulletList);
	}
}



//バフを追加する関数。バフの効果を適用し、プレイヤーのバフリストに追加する。
void Buff::addBuff(BuffEntry& buff, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList) {
	applyBuffEffect(buff, player, bulletList);
	player->mBuffList.push_back(buff);
}

//プレイヤーに弾丸を追加する
void Buff::applyBullet(BUFF_TYPE buffType, Player& player) {
	switch (buffType)
	{
	case BUFF_TYPE_BULLET_STRAIGHT:
		if(!player.isBulletTypeInSpawnList(BULLET_TYPE_PLAYER_STRAIGHT) && 
			!player.isBulletTypeInSpawnList(BULLET_TYPE_PLAYER_TRIANGLE)) 
		{
			player.AddBulletSpawnData({ BULLET_TYPE_PLAYER_STRAIGHT, 0.10f, 0.0f });
		}
		break;
	case BUFF_TYPE_BULLET_BOTTOMLEFT:
		if(!player.isBulletTypeInSpawnList(BULLET_TYPE_PLAYER_BOTTOMLEFT)&& 
			!player.isBulletTypeInSpawnList(BULLET_TYPE_PLAYER_TRIANGLE))
		{
			player.AddBulletSpawnData({ BULLET_TYPE_PLAYER_BOTTOMLEFT, 0.10f, 0.0f });
		}
		break;
	case BUFF_TYPE_BULLET_TOPRIGHT:
		if(!player.isBulletTypeInSpawnList(BULLET_TYPE_PLAYER_TOPRIGHT) && 
			!player.isBulletTypeInSpawnList(BULLET_TYPE_PLAYER_TRIANGLE))
		{
			player.AddBulletSpawnData({ BULLET_TYPE_PLAYER_TOPRIGHT, 0.10f, 0.0f });
		}
		break;
	}
}

bool Buff::isBullet(BUFF_TYPE buffType) const
{
	return buffType == BUFF_TYPE_BULLET_STRAIGHT || 
		buffType == BUFF_TYPE_BULLET_BOTTOMLEFT || 
		buffType == BUFF_TYPE_BULLET_TOPRIGHT;
}

//バフの種類をランダムに取得する関数。最大スタックに達していないバフを返す。
BUFF_TYPE Buff::getRandomBuff(Player* player) const 
{
	while (true)
	{
		BUFF_TYPE randomBuffType = static_cast<BUFF_TYPE> (rand() % BUFF_TYPE_MAX);

		auto it = std::find_if(buffTable.begin(), buffTable.end(), [randomBuffType](const BuffTable& b) {
			return b.buffType == randomBuffType;
		});

		if (it != buffTable.end())
		{
			bool isMax = it->isMaxCount;

			if (isMax)
			{
				continue;
			}
			else
			{
				return randomBuffType;
			}
		}
	}
}

//バフの値を取得する関数。
float Buff::getBuffValue(BUFF_TYPE buffType, int count) const {
	switch (buffType) {
	case BUFF_TYPE_SPEED:
		return getSpeedBuffValue(count);
	case BUFF_TYPE_POWER:
		return getPowerBuffValue(count);
	case BUFF_TYPE_DEFENSE:
		return getDefenseBuffValue(count);
	case BUFF_TYPE_BULLET_SPEED:
		return bulletSpeedBuffValueTable[count];
	case BUFF_TYPE_BULLET_POWER:
		return bulletPowerBuffValueTable[count];
	default:
		return 0.0f;
	}
}

//バフのスタックを取得する関数。
int Buff::getBuffCount(BUFF_TYPE buffType, Player* player) const {
	BuffEntry* buff = hasBuff(buffType, player->mBuffList);
	if (buff != nullptr) {
		return buff->count;
	}
	return 0;
}

//バフの最大スタックを取得する関数。
size_t Buff::getMaxBuffCount(BUFF_TYPE buffType) const {
	switch (buffType) {
	case BUFF_TYPE_SPEED:
		return speedBuffValueTable.size();
	case BUFF_TYPE_POWER:
		return powerBuffValueTable.size();
	case BUFF_TYPE_DEFENSE:
		return defenseBuffValueTable.size();
	case BUFF_TYPE_BULLET_SPEED:
		return bulletSpeedBuffValueTable.size();
	case BUFF_TYPE_BULLET_POWER:
		return bulletPowerBuffValueTable.size();
	case BUFF_TYPE_NONE:
		return 1000;
	default:
		return 0;
	}
}

//バフが存在するかを確認する関数。
BuffEntry* Buff::hasBuff(BUFF_TYPE buffType, const std::vector<BuffEntry>& buffList) const {
	for (const auto& buff : buffList) {
		if (buff.buffType == buffType) {
			return const_cast<BuffEntry*>(&buff);
		}
	}
	return nullptr;
}


const BuffTable* Buff::getBuffTable(BUFF_TYPE buffType) const {
	auto it = std::find_if(buffTable.begin(), buffTable.end(), [buffType](const BuffTable& b) {
		return b.buffType == buffType;
	});

	if (it != buffTable.end()) {
		return &(*it);
	}
	return nullptr;
}



SDL_Texture* Buff::getBuffTexture(BUFF_TYPE buffType, TTF_Font* font, SDL_Renderer* renderer, SDL_Rect& rect, Player* player) {
	std::string buffText = getBuffText(buffType, getBuffCount(buffType, player));

	SDL_Color textColor = { 255, 255, 255, 255 }; // White color
	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, buffText.c_str(), textColor, 0);
	if (surface == nullptr) {
		SDL_Log("Failed to create surface for buff text: %s", TTF_GetError());
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* Buff::getBuffImageTexture(BUFF_TYPE buffType, SDL_Renderer* renderer) {
	std::string imagePath = Loader::buffTypeToFilePath(buffType);
	SDL_Texture* imageTexture = IMG_LoadTexture(renderer, imagePath.c_str());
	if (imageTexture == nullptr) {
		SDL_Log("Failed to load buff image: %s", IMG_GetError());
		return nullptr;
	}
	return imageTexture;
}

std::string Buff::getBuffText(BUFF_TYPE buffType, int count) {
	std::ostringstream oss;
	switch (buffType) {
	case BUFF_TYPE_SPEED:
		oss << "speed up" << std::to_string(static_cast<int>(speedBuffValueTable[count])) << "%";
		return oss.str();
	case BUFF_TYPE_POWER:
		oss << "power up" << std::to_string(static_cast<int>(powerBuffValueTable[count])) << "%";
		return oss.str();
	case BUFF_TYPE_DEFENSE:
		oss << "defense up" << std::to_string(static_cast<int>(defenseBuffValueTable[count])) << "%";
		return oss.str();
	case BUFF_TYPE_BULLET_SPEED:
		oss << "bullet speed up" << std::to_string(static_cast<int>(bulletSpeedBuffValueTable[count])) << "%";
		return oss.str();
	case BUFF_TYPE_BULLET_POWER:
		oss << "bullet power up" << std::to_string(static_cast<int>(bulletPowerBuffValueTable[count])) << "%";
		return oss.str();
	case BUFF_TYPE_BULLET_STRAIGHT:
		return "Straight Bullet";
	case BUFF_TYPE_BULLET_BOTTOMLEFT:
		return "Bottom Left Bullet";
	case BUFF_TYPE_BULLET_TOPRIGHT:
		return "Top Right Bullet";
	case BUFF_TYPE_NONE:
		return "No Buff";
	default:
		return "Unknown Buff";
	}
}



void Buff::applyBuffEffect(BuffEntry& buff, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList) {
	switch (buff.buffType) {
		case BUFF_TYPE_SPEED:	player->status.speed += buff.buffValue;
			break;
		case BUFF_TYPE_POWER:	player->status.power += buff.buffValue;
			break;
		case BUFF_TYPE_DEFENSE:	player->status.defense += buff.buffValue;
			break;
		case BUFF_TYPE_BULLET_SPEED:	applyBuffEffectForBullet(buff, bulletList);
			break;
		case BUFF_TYPE_BULLET_POWER:	applyBuffEffectForBullet(buff, bulletList);
			break;
		default:
			break;
	}
}

void Buff::removeBuffEffect(BuffEntry& buff, Player* player, std::vector<std::unique_ptr<Bullet>>& bulletList) {
	switch (buff.buffType) {
	case BUFF_TYPE_SPEED:	player->status.speed -= buff.buffValue;
		break;
	case BUFF_TYPE_POWER:	player->status.power -= buff.buffValue;
		break;
	case BUFF_TYPE_DEFENSE:	player->status.defense -= buff.buffValue;
		break;
	case BUFF_TYPE_BULLET_SPEED:
	case BUFF_TYPE_BULLET_POWER:	removeBuffEffectForBullet(buff, bulletList);
		break;
	default:
		break;
	}
}

void Buff::applyBuffEffectForBullet(BuffEntry& buff, std::vector<std::unique_ptr<Bullet>>& bulletList) 
{
	for (auto& bullet : bulletList)
	{
		switch (buff.buffType) {
		case BUFF_TYPE_BULLET_SPEED:
			bullet->status.speed += buff.buffValue;
			break;
		case BUFF_TYPE_BULLET_POWER:
			bullet->status.power += buff.buffValue;
			break;
		default:
			break;	
		}
	}
}

void Buff::removeBuffEffectForBullet(BuffEntry& buff, std::vector<std::unique_ptr<Bullet>>& bulletList) 
{
	for (auto& bullet : bulletList)
	{
		switch (buff.buffType) {
		case BUFF_TYPE_BULLET_SPEED:
			bullet->status.speed -= buff.buffValue;
			break;
		case BUFF_TYPE_BULLET_POWER:
			bullet->status.power -= buff.buffValue;
			break;
		default:
			break;	
		}
	}
}

bool Buff::isMaxBuffCount(int count, int maxCount) const {
	if (count >= maxCount) {
		return true;
	}
	return false;
}
