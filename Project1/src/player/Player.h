#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "../common/Status.h"
#include "../bullet/BulletType.h"
#include "../common/LevelTable.h"

class Player {
public:
	Player();
	~Player();

	Status status;
	std::string mPlayerName;

	std::vector <BuffEntry> mBuffList;

	virtual void Initialize(int screenWidth, int screenHeight);
	virtual void InitializeBulletSpawnList();
	virtual void ProcessInput(const Uint8* keyState);
	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

	inline void Destroy() { mIsActive = false; };
	inline void OnHit() { mIsHit = true; };

	inline bool IsActive() const { return mIsActive; }

	inline void SetPlayerTexture(SDL_Texture* texture) { mPlayerTexture = texture; }

	inline float GetPosX() const {return static_cast<float>(mRect.x);}
	inline float GetPosY() const { return static_cast<float>(mRect.y);}
	void SetPosition(float x, float y);
	inline int GetWidth() const { return mRect.w; }
	inline int GetHeight() const { return mRect.h; }
	SDL_Rect& GetRect() { return mRect; }

	//SpawnList関連の関数
	bool isBulletTypeInSpawnList(BULLET_TYPE bulletType);
	void AddBulletSpawnData(BulletSpawnData spawnData);

	inline float GetExp() const { return mExp; }
	inline void SetExp(float exp) { mExp = exp; }
	inline void AddExp(float exp) { mExp += exp; }
	inline void ResetExp() { mExp = 0.0f; }
	inline float GetMaxExp() const { return mMaxExp; }
	inline LEVEL_NUMBER GetCurrentLevel() const { return mCurrentLevel; }
	inline void SetMaxExp(LEVEL_NUMBER level) { mMaxExp =  GetMaxExpForLevel(level); };
	inline void SetNextLevel(LEVEL_NUMBER currentLevel) { mCurrentLevel = GetNextLevel(currentLevel); }
	inline void SetNextHp() { status.maxHealth *= 1.2f; status.health *= 1.4f; }
	inline void ClampHp() { if (status.health > status.maxHealth) status.health = status.maxHealth; }
	void ClampPos();

	inline std::vector<BulletSpawnData>& GetBulletSpawnList() { return mBulletSpawnList; }
	

protected:
	SDL_Rect mRect;
	std::vector<BulletSpawnData> mBulletSpawnList;

	float mPosX;
	float mPosY;
	int mScreenWidth;
	int mScreenHeight;

	float mFlashTime;
	float mElapsedTime;

	bool mMoveUp;
	bool mMoveDown;
	bool mMoveLeft;
	bool mMoveRight;

	bool mIsHit;
	bool mIsActive;

	float mExp;
	float mMaxExp;

	LEVEL_NUMBER mCurrentLevel;


	SDL_Texture* mPlayerTexture; // プレイヤーのテクスチャ
};
