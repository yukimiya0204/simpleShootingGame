#include "BulletLoader.h"

// Load player bullet JSON data
BulletStatus BulletLoader::loadPlayerBullet(const std::string& bulletTypeStr)
{
	BulletStatus status = BulletStatus_Init();

	// file path
	std::string filepath = dataPath("playersBullet.json");
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

	// Ensure requested bullet exists
	if (!j.contains(bulletTypeStr)) {
		throw std::runtime_error("Bullet not found: " + bulletTypeStr);
		return status;
	}
	// Retrieve bullet JSON data
	const json& bulletJson = j[bulletTypeStr];
	status.speed = bulletJson.value("speed", 0.0f);
	status.power = bulletJson.value("power", 0.0f);
	status.width = bulletJson.value("width", 0);
	status.height = bulletJson.value("height", 0);
	status.angle = bulletJson.value("angle", 0.0f);
	
	return status;
}


// Load enemy bullet JSON data
BulletStatus BulletLoader::loadEnemyBullet(const std::string& bulletTypeStr)
{
	BulletStatus status = BulletStatus_Init();
	// file path
	std::string filepath = dataPath("enemysBullet.json");
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
	// Ensure requested bullet exists
	if (!j.contains(bulletTypeStr)) {
		throw std::runtime_error("Bullet not found: " + bulletTypeStr);
		return status;
	}
	// Retrieve bullet JSON data
	const json& bulletJson = j[bulletTypeStr];
	status.speed = bulletJson.value("speed", 0.0f);
	status.power = bulletJson.value("power", 0.0f);
	status.width = bulletJson.value("width", 0);
	status.height = bulletJson.value("height", 0);
	status.angle = bulletJson.value("angle", 0.0f);
	return status;
}