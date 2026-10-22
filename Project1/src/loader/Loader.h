#pragma once

#include "nlohmann/json.hpp"

#include "../common/Type.h"
#include "../common/LevelTable.h"

using json = nlohmann::json;

class Loader 
{
public:
	static std::string levelToString(LEVEL_NUMBER level);
	static std::string phaseToString(PHASE_NUMBER phase);
	static std::string enemyTypeToString(ENEMY_TYPE enemyType);
	static std::string bulletTyepToString(BULLET_TYPE bulletType);
	static std::string playerIdToString(PLAYER_ID playerId);
	static std::string buffTypeToFilePath(BUFF_TYPE buffType);
	static std::string buffTypeToString(BUFF_TYPE buffType);

	static LEVEL_NUMBER stringToLevel(const std::string& levelStr);
	static PHASE_NUMBER stringToPhase(const std::string& phaseStr);
	static ENEMY_TYPE stringToEnemyType(const std::string& enemyTypeStr);
	static BULLET_TYPE stringToBulletType(const std::string& bulletTypeStr);
	static PLAYER_ID stringToPlayerId(const std::string& playerIdStr);
	static BUFF_TYPE stringToBuffType(const std::string& buffTypeStr);

protected:
	static std::string dataPath(const std::string& filepath);
};
