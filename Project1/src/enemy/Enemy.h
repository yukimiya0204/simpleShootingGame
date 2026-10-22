#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../common/Vector.h"
#include "../common/Status.h"
#include "../bullet/BulletType.h"

class Player;

class Enemy {
public:
	Enemy();

	EnemyStatus status;
	ENEMY_TYPE mEnemyType;
	std::string mEnemyName;

	virtual void Initialize(int screenWidth, int screenHeight);
	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);
	virtual void OnHit();

	// 追加: 敵が弾生成情報を持つ
	virtual void InitializeBulletSpawnList();
	inline std::vector<BulletSpawnData>& GetBulletSpawnList() { return mBulletSpawnList; }
	
	inline float GetHitPower() const { return status.baseHitAttack; }
	inline float GetHaveExp() const	{ return status.exp; }
	inline float GetPosX() const { return mPosition.x; }
	inline float GetPosY() const { return mPosition.y; }

	inline bool IsOffScreen() const { return mPosition.x + mRect.w < 0; }
	inline SDL_Rect& GetRect() { return mRect; }
	void SetPosition(float x, float y);
	void ClampPos();
	inline bool IsActive() const { return mIsActive; }
	inline void Destroy() { mIsActive = false; }

	void SetTargetPlayer(Player* player) { mTargetPlayer = player; } // 追加: プレイヤーへの参照を設定
	Player* GetTargetPlayer() const { return mTargetPlayer; } // 追加: プレイヤーへの参照を取得

	

protected:
	SDL_Rect mRect;

	Vector2 mPosition;
	int mScreenWidth;
	int mScreenHeight;
	bool mIsActive;

	float mFlashTime;
	float mElapsedTime;
	bool mIsHit;

	std::vector<BulletSpawnData> mBulletSpawnList; // 追加
	
	Player* mTargetPlayer; // 追加: プレイヤーへの参照
};