#pragma once

#include <string>
#include <fstream>

#include "../Loader.h"
#include "../../common/Status.h"

class CharacterLoader : public Loader
{
public:
	static Status loadCharacterStatus(const std::string& name);
	static EnemyStatus loadEnemyStatus(const std::string& name);


private:

};