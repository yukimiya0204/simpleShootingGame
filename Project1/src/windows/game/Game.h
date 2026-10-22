#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <memory>

#include "../BaseWindow.h"

#include "../../player/Player.h"
#include "../../enemy/Phase.h"
#include "../../enemy/Enemy.h"
#include "../../bullet/BulletType.h"
#include "../../bullet/Bullet.h"
#include "../../bar/bars/ExpBar.h"
#include "../../bar/bars/HpBar.h"
#include "../../common/Buff.h"
#include "../../common/calcDamage/Calc.h"
#include "../../lib/myCardLibrary.h"

class Game : public BaseWindow {
public:
	Game();
	~Game();

	void Main();

	bool Initialize() override;
	void RunLoop() override;
	void Shutdown() override;
	void SetSelectedPlayerId(PLAYER_ID playerId) { mSelectedPlayerId = playerId; }
	RESULT getResult() const { return mResult; }

private:
	void ProcessInput() override;
	void Update() override;
	void GenerateOutput() override;

   void InitializeBar(); // バー初期化
	void UpdateLevelText(); // レベル表示更新

 void InitializePhase(); // フェーズ初期化
	void InitializePlayer(); // プレイヤー初期化
	void SpawnEnemy(ENEMY_TYPE enemyType); // 敵を生成
	void InitializeBulletSpawnList(); // 弾発射設定初期化
	void SpawnBullet(BULLET_TYPE bulletType); // 自弾を生成
	void SpawnEnemyBullet(Enemy* shooterEnemy, BULLET_TYPE bulletType); // 敵弾を生成

	//バフを表示する配列に格納する関数
	void AddBuffToList(BUFF_TYPE buffType);

	//プレイヤーと敵に当たり判定をつける関数
	void CheckCollisionBetweenPlayerAndEnemy(Player& player, Enemy& enemy, SDL_Rect& intersection);



	inline void CalcDamageToEnemy(Enemy& enemy, Bullet& bullet) { enemy.status.health -= bullet.GetBulletPower(); };
	inline void CalcDamageToPlayer(Player& player, Bullet& bullet) { player.status.health -= bullet.GetBulletPower(); };
	inline void CalcHitDamageToPlayer(Player& player, Enemy& enemy) { player.status.health -= enemy.status.baseHitAttack; };
	inline void CalcHitDamageToEnemy(Player& player, Enemy& enemy) { enemy.status.health -= player.status.baseHitAttack; };

	inline SDL_Renderer* GetRenderer() { return mRenderer; }

	Calc mCalc;
	//勝敗結果
	RESULT mResult;

	//選択されたプレイヤーのID
	PLAYER_ID mSelectedPlayerId;
	//SDL関連
	SDL_Texture* mTexture;
	SDL_Texture* mBuffTexture;
	SDL_Texture* mBuffImageTexture;
	SDL_Texture* mTextTexture;

	SDL_Rect mTextRect;
	std::vector<SDL_Rect> mBuffTextRects;
	std::vector<SDL_Rect> mBuffImageRects;
	TTF_Font* mLevelFont;
	TTF_Font* mBuffFont;

	//ループ制御
	bool mIsRunning;
	Uint32 mTicksCount;

	//ゲームオブジェクト
	std::unique_ptr<Player> mPlayer;
	std::vector<std::unique_ptr<Enemy>> mEnemies;
	std::vector<std::unique_ptr<Bullet>> mBullets;
	std::vector<std::unique_ptr<Bullet>> mEnemyBullets;
	ExpBar mExpBar;
	HpBar mHpBar;

	float mSpawnTimer;
	float mBulletSpawnTimer;
	int mExpBarWidth;
	int mExpBarHeight;
	int mHpBarWidth;
	int mHpBarHeight;

	//バフ管理
	Buff mBuff;
	std::vector<BUFF_TYPE> mBuffList;
	std::vector<BuffTextureData*> mBuffTextures;

	//フェーズ管理
	std::vector<Phase> mPhases;
	size_t mCurrentPhaseIndex;
	size_t mCurrentEnemyIndex;


	//画面切り替え
	bool mIsRooleting;
	BigCard mRectangleCard1;
	BigCard mRectangleCard2;
	BigCard mRectangleCard3;
	DetailCard mDetailCard1;
	DetailCard mDetailCard2;
	DetailCard mDetailCard3;
	IconCard mIconCard1;
	IconCard mIconCard2;
	IconCard mIconCard3;

	//カードの色変化(カーソルを持ってきたとき)
	bool mIsCursolOnCard1;
	bool mIsCursolOnCard2;
	bool mIsCursolOnCard3;
	SDL_Texture* mWhiteRectangleTexture;
	SDL_Texture* mBlueRectangleTexture;
	SDL_Texture* mWhiteDetailTexture;
	SDL_Texture* mWhiteIconTexture;
};