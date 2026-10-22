#pragma once

#include <SDL2/SDL.h>

class Enemy;

typedef enum {
	WIN,
	LOSE,
	RESULT_MAX
}RESULT;

//number of phases
typedef enum {
	PHASE_1,
	PHASE_2,
	PHASE_3,
	PHASE_MAX
} PHASE_NUMBER;

//enemy types
typedef enum {
	ENEMY_TYPE_ENEMY,
	ENEMY_TYPE_FASTENEMY,
	ENEMY_TYPE_SHOOTERENEMY,
	ENEMY_TYPE_SINSHOOTERENEMY,
	ENEMY_TYPE_FOLLOWTARGETENEMY,
	ENEMY_TYPE_MAX
} ENEMY_TYPE;

//player types
typedef enum {
	SIMPLEPLAYER_ID,
	SPEEDPLAYER_ID,
	PLAYER_ID_MAX
}PLAYER_ID;

//bullet types 
typedef enum {
	//PLAYER BULLET
	BULLET_TYPE_PLAYER_STRAIGHT,
	BULLET_TYPE_PLAYER_BOTTOMLEFT,
	BULLET_TYPE_PLAYER_TOPRIGHT,
	BULLET_TYPE_PLAYER_TRIANGLE,
	BULLET_TYPE_PLAYER_SIN,
	//ENEMY BULLET
	BULLET_TYPE_ENEMY_STRAIGHT,
	BULLET_TYPE_ENEMY_BOTTOMLEFT,
	BULLET_TYPE_ENEMY_TOPRIGHT,
	BULLET_TYPE_ENEMY_TRIANGLE,
	BULLET_TYPE_ENEMY_SIN,
	BULLET_TYPE_MAX
} BULLET_TYPE;

//enemy bullet spawn data
struct EnemyBulletSpawnData {
	Enemy* enemy;
	BULLET_TYPE bulletType;
	float spawnInterval;		// The spawn interval of this bullet (seconds)
	float currentSpawnTimer;	// The current spawn timer

};

//buff types
typedef enum {
	BUFF_TYPE_SPEED,
	BUFF_TYPE_POWER,
	BUFF_TYPE_DEFENSE,
	BUFF_TYPE_BULLET_SPEED,
	BUFF_TYPE_BULLET_POWER,
	BUFF_TYPE_BULLET_STRAIGHT,
	BUFF_TYPE_BULLET_BOTTOMLEFT,
	BUFF_TYPE_BULLET_TOPRIGHT,
	BUFF_TYPE_NONE,
	BUFF_TYPE_MAX
}BUFF_TYPE;

// buff Entry structure
struct BuffEntry {
	BUFF_TYPE buffType;
	float buffValue;
	int count; 
	int maxCount;
};

//buff table structure
struct BuffTable {
	BUFF_TYPE buffType;
	bool isMaxCount;
};

struct BuffTextureData {
	SDL_Texture* texture;
	SDL_Rect rect;
	BUFF_TYPE buffType;
};