#pragma once

#include <string>
#include <fstream>

#include "../Loader.h"
#include "../../bullet/BulletStatus.h"

class BulletLoader : public Loader
{
public:

	static BulletStatus loadPlayerBullet(const std::string& bulletTypeStr);
	static BulletStatus loadEnemyBullet(const std::string& bulletTypeStr);

};