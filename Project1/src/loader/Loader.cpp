#include <fstream>
#include <cstdio>

#include "Loader.h"

// ===================================
// JSON data helpers
// ===================================
std::string Loader::dataPath(const std::string& filepath)
{
	return "src/loader/data/" + filepath;
}

// ===================================
// Level/phase conversion helpers
// ===================================

std::string Loader::levelToString(LEVEL_NUMBER level)
{
	switch (level)
	{
	case LEVEL_1:	return "LEVEL_1";
	case LEVEL_2:	return "LEVEL_2";
	case LEVEL_3:	return "LEVEL_3";
	case LEVEL_4:	return "LEVEL_4";
	case LEVEL_5:	return "LEVEL_5";
	case LEVEL_6:	return "LEVEL_6";
	case LEVEL_7:	return "LEVEL_7";
	default:
		return "UNKNOWN_LEVEL";
	}
}

std::string Loader::phaseToString(PHASE_NUMBER phase)
{
	switch (phase)
	{
	case PHASE_1:	return "PHASE_1";
	case PHASE_2:	return "PHASE_2";
	case PHASE_3:	return "PHASE_3";
	default:
		return "UNKNOWN_PHASE";
	}
}

std::string Loader::enemyTypeToString(ENEMY_TYPE enemyType)
{
	switch (enemyType)
	{
	case ENEMY_TYPE_ENEMY:			return "ENEMY_TYPE_ENEMY";
	case ENEMY_TYPE_FASTENEMY:		return "ENEMY_TYPE_FASTENEMY";
	case ENEMY_TYPE_SHOOTERENEMY:	return "ENEMY_TYPE_SHOOTERENEMY";
	case ENEMY_TYPE_SINSHOOTERENEMY:return "ENEMY_TYPE_SINSHOOTERENEMY";
	case ENEMY_TYPE_FOLLOWTARGETENEMY:	return "ENEMY_TYPE_FOLLOWTARGETENEMY";
	default:
		return "UNKNOWN_ENEMY_TYPE";
	}
}

std::string Loader::bulletTyepToString(BULLET_TYPE bulletType)
{
	switch (bulletType)
	{
	case BULLET_TYPE_PLAYER_STRAIGHT:	return "BULLET_TYPE_PLAYER_STRAIGHT";
	case BULLET_TYPE_PLAYER_BOTTOMLEFT:	return "BULLET_TYPE_PLAYER_BOTTOMLEFT";
	case BULLET_TYPE_PLAYER_TOPRIGHT:	return "BULLET_TYPE_PLAYER_TOPRIGHT";
	case BULLET_TYPE_PLAYER_TRIANGLE:	return "BULLET_TYPE_PLAYER_TRIANGLE";
	case BULLET_TYPE_PLAYER_SIN:		return "BULLET_TYPE_PLAYER_SIN";
	case BULLET_TYPE_ENEMY_STRAIGHT:	return "BULLET_TYPE_ENEMY_STRAIGHT";
	case BULLET_TYPE_ENEMY_BOTTOMLEFT:	return "BULLET_TYPE_ENEMY_BOTTOMLEFT";
	case BULLET_TYPE_ENEMY_TOPRIGHT:	return "BULLET_TYPE_ENEMY_TOPRIGHT";
	case BULLET_TYPE_ENEMY_TRIANGLE:	return "BULLET_TYPE_ENEMY_TRIANGLE";
	case BULLET_TYPE_ENEMY_SIN:		return "BULLET_TYPE_ENEMY_SIN";
	default:
		return "UNKNOWN_BULLET_TYPE";
	}
}

std::string Loader::playerIdToString(PLAYER_ID playerId)
{
	switch (playerId)
	{
	case SIMPLEPLAYER_ID:			return "SIMPLEPLAYER_ID";
	case SPEEDPLAYER_ID:			return "SPEEDPLAYER_ID";
	default:
		return "UNKNOWN_CHARACTER_ID";
	}
}

std::string Loader::buffTypeToString(BUFF_TYPE buffType)
{
	switch (buffType)
	{
	case BUFF_TYPE_SPEED:	return "BUFF_TYPE_SPEED";
	case BUFF_TYPE_POWER:	return "BUFF_TYPE_POWER";
	case BUFF_TYPE_DEFENSE:	return "BUFF_TYPE_DEFENSE";
	case BUFF_TYPE_BULLET_SPEED:	return "BUFF_TYPE_BULLET_SPEED";
	case BUFF_TYPE_BULLET_POWER:	return "BUFF_TYPE_BULLET_POWER";
	case BUFF_TYPE_NONE:	return "BUFF_TYPE_NONE";
	default:
		return "UNKNOWN_BUFF_TYPE";
	}
}

std::string Loader::buffTypeToFilePath(BUFF_TYPE buffType)
{
	const std::string basePath = "assets/images/";
	switch (buffType)
	{
	case BUFF_TYPE_SPEED:	return basePath + "speed.png";
	case BUFF_TYPE_POWER:	return basePath + "power.png";
	case BUFF_TYPE_DEFENSE:	return basePath + "defense.png";
	case BUFF_TYPE_NONE:	return "none.png";
	default:
		return "unknown.png";
	}
}

// ===================================
// String to enum helpers
// ===================================

LEVEL_NUMBER Loader::stringToLevel(const std::string& levelStr)
{
	if (levelStr == "LEVEL_1") return LEVEL_1;
	if (levelStr == "LEVEL_2") return LEVEL_2;
	if (levelStr == "LEVEL_3") return LEVEL_3;
	if (levelStr == "LEVEL_4") return LEVEL_4;
	if (levelStr == "LEVEL_5") return LEVEL_5;
	if (levelStr == "LEVEL_6") return LEVEL_6;
	if (levelStr == "LEVEL_7") return LEVEL_7;
	return LEVEL_MAX; // Unknown level
}

PHASE_NUMBER Loader::stringToPhase(const std::string& phaseStr)
{
	if (phaseStr == "PHASE_1") return PHASE_1;
	if (phaseStr == "PHASE_2") return PHASE_2;
	if (phaseStr == "PHASE_3") return PHASE_3;
	return PHASE_MAX; // Unknown phase
}

ENEMY_TYPE Loader::stringToEnemyType(const std::string& enemyTypeStr)
{
	if (enemyTypeStr == "ENEMY_TYPE_ENEMY") return ENEMY_TYPE_ENEMY;
	if (enemyTypeStr == "ENEMY_TYPE_FASTENEMY") return ENEMY_TYPE_FASTENEMY;
	if (enemyTypeStr == "ENEMY_TYPE_SHOOTERENEMY") return ENEMY_TYPE_SHOOTERENEMY;
	if (enemyTypeStr == "ENEMY_TYPE_SINSHOOTERENEMY") return ENEMY_TYPE_SINSHOOTERENEMY;
	if (enemyTypeStr == "ENEMY_TYPE_FOLLOWTARGETENEMY") return ENEMY_TYPE_FOLLOWTARGETENEMY;
	return ENEMY_TYPE_MAX; // Unknown enemy type
}

BULLET_TYPE Loader::stringToBulletType(const std::string& bulletTypeStr)
{
	if (bulletTypeStr == "BULLET_TYPE_PLAYER_STRAIGHT") return BULLET_TYPE_PLAYER_STRAIGHT;
	if (bulletTypeStr == "BULLET_TYPE_PLAYER_BOTTOMLEFT") return BULLET_TYPE_PLAYER_BOTTOMLEFT;
	if (bulletTypeStr == "BULLET_TYPE_PLAYER_TOPRIGHT") return BULLET_TYPE_PLAYER_TOPRIGHT;
	if (bulletTypeStr == "BULLET_TYPE_PLAYER_TRIANGLE") return BULLET_TYPE_PLAYER_TRIANGLE;
	if (bulletTypeStr == "BULLET_TYPE_PLAYER_SIN") return BULLET_TYPE_PLAYER_SIN;
	if (bulletTypeStr == "BULLET_TYPE_ENEMY_STRAIGHT") return BULLET_TYPE_ENEMY_STRAIGHT;
	if (bulletTypeStr == "BULLET_TYPE_ENEMY_BOTTOMLEFT") return BULLET_TYPE_ENEMY_BOTTOMLEFT;
	if (bulletTypeStr == "BULLET_TYPE_ENEMY_TOPRIGHT") return BULLET_TYPE_ENEMY_TOPRIGHT;
	if (bulletTypeStr == "BULLET_TYPE_ENEMY_TRIANGLE") return BULLET_TYPE_ENEMY_TRIANGLE;
	if (bulletTypeStr == "BULLET_TYPE_ENEMY_SIN") return BULLET_TYPE_ENEMY_SIN;
	return BULLET_TYPE_MAX; // Unknown bullet type
}

PLAYER_ID Loader::stringToPlayerId(const std::string& playerIdStr)
{
	if (playerIdStr == "SIMPLEPLAYER_ID") return SIMPLEPLAYER_ID;
	if (playerIdStr == "SPEEDPLAYER_ID") return SPEEDPLAYER_ID;
	return PLAYER_ID_MAX; // Unknown player ID
}

BUFF_TYPE Loader::stringToBuffType(const std::string& buffTypeStr)
{
	if (buffTypeStr == "BUFF_TYPE_SPEED") return BUFF_TYPE_SPEED;
	if (buffTypeStr == "BUFF_TYPE_POWER") return BUFF_TYPE_POWER;
	if (buffTypeStr == "BUFF_TYPE_DEFENSE") return BUFF_TYPE_DEFENSE;
	if (buffTypeStr == "BUFF_TYPE_NONE") return BUFF_TYPE_NONE;
	return BUFF_TYPE_MAX; // Unknown buff type
}






