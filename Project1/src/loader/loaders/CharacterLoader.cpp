#include "CharacterLoader.h"

Status CharacterLoader::loadCharacterStatus(const std::string& name)
{
	Status status = Status_Init();

	// file path
	std::string filepath = dataPath("players.json");
	std::ifstream file(filepath);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filepath);
		return status;
	}

	json j;
	try {
		file >> j;
	}
	catch (...) {
		throw std::runtime_error("Failed to parse JSON file: " + filepath);
		return status;
	}

	// Check that the requested character exists
	if(!j.contains(name)) {
		throw std::runtime_error("Character not found: " + name);
		return status;
	}

	// Retrieve character JSON data
	const json& characterJson = j[name];
	status.width = characterJson.value("width", 0);
	status.height = characterJson.value("height", 0);

	status.baseHp = characterJson.value("baseHp", 0.0f);
	status.baseSpeed = characterJson.value("baseSpeed", 0.0f);
	status.basePower = characterJson.value("basePower", 0.0f);
	status.baseHitAttack = characterJson.value("baseHitAttack", 0.0f);
	status.baseDefense = characterJson.value("baseDefense", 0.0f);
	status.knockbackDistance = characterJson.value("knockbackDistance", 0.0f);
	
	status.maxHealth = status.baseHp;
	status.health = status.maxHealth;
	status.speed = status.baseSpeed;
	status.power = status.basePower;
	status.defense = status.baseDefense;

	return status;
}

EnemyStatus CharacterLoader::loadEnemyStatus(const std::string& name)
{
	EnemyStatus status;
	// file path
	std::string filepath = dataPath("enemys.json");
	std::ifstream file(filepath);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filepath);
		return status;
	}
	json j;
	try {
		file >> j;
	}
	catch (...) {
		throw std::runtime_error("Failed to parse JSON file: " + filepath);
		return status;
	}
	// Check that the requested enemy exists
	if(!j.contains(name)) {
		throw std::runtime_error("Enemy not found: " + name);
		return status;
	}
	// Retrieve enemy JSON data
	const json& enemyJson = j[name];
	status.width = enemyJson.value("width", 0);
	status.height = enemyJson.value("height", 0);

	status.baseHp = enemyJson.value("baseHp", 0.0f);
	status.baseSpeed = enemyJson.value("baseSpeed", 0.0f);
	status.basePower = enemyJson.value("basePower", 0.0f);
	status.baseHitAttack = enemyJson.value("baseHitAttack", 0.0f);
	status.baseDefense = enemyJson.value("baseDefense", 0.0f);
	status.knockbackDistance = enemyJson.value("knockbackDistance", 0.0f);
	
	status.maxHealth = status.baseHp;
	status.health = status.maxHealth;
	status.speed = status.baseSpeed;
	status.power = status.basePower;
	status.defense = status.baseDefense;

	status.exp = enemyJson.value("exp", 0.0f);
	return status;
}

