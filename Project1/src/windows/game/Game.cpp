#include <ctime>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "Game.h"

#include "../../bar/Bar.h"
#include "../../loader/Loader.h"
#include "../../player/players/SimplePlayer.h"
#include "../../player/players/SpeedPlayer.h"
#include "../../enemy/enemies/FastEnemy.h"
#include "../../enemy/enemies/FollowTargetEnemy.h"
#include "../../enemy/enemies/ShooterEnemy.h"
#include "../../enemy/enemies/SinShooterEnemy.h"
#include "../../lib/myBulletLibrary.h"

//-------------------------------------------------
//Display the game window and handle the game loop	
//-------------------------------------------------


namespace
{
	const int SCREEN_WIDTH = 640;					// スクリーン画面幅
	const int SCREEN_HEIGHT = 480;					// スクリーン画面高さ

  const int EXP_BAR_WIDTH = 100;				// EXPバー幅
	const int EXP_BAR_HEIGHT = 20;				// EXPバー高さ
	const int HP_BAR_WIDTH = 100;				// HPバー幅
	const int HP_BAR_HEIGHT = 20;				// HPバー高さ
	const int TEXT_POS_X = 50;					// レベルテキストx座標
	const int TEXT_POS_Y = 0;					// レベルテキストy座標

 const int BUFF_TEXT_POS_X = 40;				// バフテキスト基準x座標
	const int BUFF_TEXT_POS_Y = 200;				// バフテキスト基準y座標
	const int BUFF_IMAGE_POS_X = 65;				// バフ画像基準x座標
	const int BUFF_IMAGE_POS_Y = 70;				// バフ画像基準y座標
	const int BUFF_IMAGE_WIDTH = 90;				// バフ画像基準幅
	const int BUFF_IMAGE_HEIGHT = 90;				// バフ画像基準高さ


    const int RECTANGLECARD1_POS_X = 15;			// 大枠バフカード1x座標
	const int RECTANGLECARD1_POS_Y = 50;			// 大枠バフカード1y座標
	const int RECTANGLECARD2_POS_X = 225;			// 大枠バフカード2x座標
	const int RECTANGLECARD2_POS_Y = 50;			// 大枠バフカード2y座標
	const int RECTANGLECARD3_POS_X = 435;			// 大枠バフカード3x座標
	const int RECTANGLECARD3_POS_Y = 50;			// 大枠バフカード3y座標

    const int DETAILCARD1_POS_X = RECTANGLECARD1_POS_X + 15;	// バフ詳細カード1x座標
	const int DETAILCARD1_POS_Y = RECTANGLECARD1_POS_Y + 150;	// バフ詳細カード1y座標
	const int DETAILCARD2_POS_X = RECTANGLECARD2_POS_X + 15;	// バフ詳細カード2x座標
	const int DETAILCARD2_POS_Y = RECTANGLECARD2_POS_Y + 150;	// バフ詳細カード2y座標
	const int DETAILCARD3_POS_X = RECTANGLECARD3_POS_X + 15;	// バフ詳細カード3x座標
	const int DETAILCARD3_POS_Y = RECTANGLECARD3_POS_Y + 150;	// バフ詳細カード3y座標

  const int ICONCARD1_POS_X = RECTANGLECARD1_POS_X + 45;		// バフ画像カード1x座標
	const int ICONCARD1_POS_Y = RECTANGLECARD1_POS_Y + 15;		// バフ画像カード1y座標
	const int ICONCARD2_POS_X = RECTANGLECARD2_POS_X + 45;		// バフ画像カード2x座標
	const int ICONCARD2_POS_Y = RECTANGLECARD2_POS_Y + 15;		// バフ画像カード2y座標
	const int ICONCARD3_POS_X = RECTANGLECARD3_POS_X + 45;		// バフ画像カード3x座標
	const int ICONCARD3_POS_Y = RECTANGLECARD3_POS_Y + 15;		// バフ画像カード3y座標
}


Game::Game()
	: mTexture(nullptr)
	, mTextTexture(nullptr)
	, mBuffTexture(nullptr)
	, mBuffImageTexture(nullptr)
	, mLevelFont(nullptr)
	, mBuffFont(nullptr)
	, mWhiteRectangleTexture(nullptr)
	, mBlueRectangleTexture(nullptr)
	, mWhiteDetailTexture(nullptr)
	, mWhiteIconTexture(nullptr)

	, mIsRunning(true)
	, mIsRooleting(false)
	, mIsCursolOnCard1(false)
	, mIsCursolOnCard2(false)
	, mIsCursolOnCard3(false)
	, mTicksCount(0)

	, mCurrentPhaseIndex(0)
	, mCurrentEnemyIndex(0)

	, mSpawnTimer(0.0f)
	, mBulletSpawnTimer(0.0f)
{
	//座標とサイズの初期化
	mExpBarWidth = EXP_BAR_WIDTH;
	mExpBarHeight = EXP_BAR_HEIGHT;
	mHpBarWidth = HP_BAR_WIDTH;
	mHpBarHeight = HP_BAR_HEIGHT;

	mSelectedPlayerId = SIMPLEPLAYER_ID;
	mTextRect = { TEXT_POS_X, TEXT_POS_Y, 0, 0 };
	mBuffTextRects = { { BUFF_TEXT_POS_X, BUFF_TEXT_POS_Y, 140, 20 }, { BUFF_TEXT_POS_X + 210, BUFF_TEXT_POS_Y, 140, 20 }, { BUFF_TEXT_POS_X + 420, BUFF_TEXT_POS_Y, 140, 20 } };
	mBuffImageRects = { { BUFF_IMAGE_POS_X, BUFF_IMAGE_POS_Y, BUFF_IMAGE_WIDTH, BUFF_IMAGE_HEIGHT }, 
					{ BUFF_IMAGE_POS_X + 210, BUFF_IMAGE_POS_Y, BUFF_IMAGE_WIDTH, BUFF_IMAGE_HEIGHT }, 
					{ BUFF_IMAGE_POS_X + 420, BUFF_IMAGE_POS_Y, BUFF_IMAGE_WIDTH, BUFF_IMAGE_HEIGHT } };
	mBuffList = { BUFF_TYPE_MAX, BUFF_TYPE_MAX, BUFF_TYPE_MAX };
	mResult = RESULT::RESULT_MAX;
}

Game::~Game()
{
}
// メモリ開放
void Game::Shutdown()
{
	mRectangleCard1.SetCardTexture(nullptr);
	mRectangleCard2.SetCardTexture(nullptr);
	mRectangleCard3.SetCardTexture(nullptr);
	mDetailCard1.SetCardTexture(nullptr);
	mDetailCard2.SetCardTexture(nullptr);
	mDetailCard3.SetCardTexture(nullptr);
	mIconCard1.SetCardTexture(nullptr);
	mIconCard2.SetCardTexture(nullptr);
	mIconCard3.SetCardTexture(nullptr);

	SDL_DestroyTexture(mWhiteRectangleTexture);
	mWhiteRectangleTexture = nullptr;
	SDL_DestroyTexture(mBlueRectangleTexture);
	mBlueRectangleTexture = nullptr;
	SDL_DestroyTexture(mWhiteDetailTexture);
	mWhiteDetailTexture = nullptr;
	SDL_DestroyTexture(mWhiteIconTexture);	
	mWhiteIconTexture = nullptr;	

	SDL_DestroyTexture(mTextTexture);
	mTextTexture = nullptr;
	SDL_DestroyTexture(mBuffTexture);
	mBuffTexture = nullptr;

	mLevelFont = nullptr;
	mBuffFont = nullptr; 

}



// 初期化
bool Game::Initialize()
{
	bool success = true;

	InitializePlayer();
	mPlayer->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
	InitializePhase();

	//プレイヤーの画像を読み込む
	SDL_Texture* playerTexture = IMG_LoadTexture(mRenderer, "assets/images/jett.png");
	if (playerTexture == nullptr)
	{
		SDL_Log("Failed to load player image: %s", IMG_GetError());
		success = false;
	}
	else
	{
		mPlayer->SetPlayerTexture(playerTexture);
	}
	srand(static_cast<unsigned int>(time(nullptr)));

	mTicksCount = SDL_GetTicks();
	// HPバーとEXPバーの初期化
	mExpBar.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, mExpBarWidth, mExpBarHeight);
	mHpBar.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, mHpBarWidth, mHpBarHeight);
	// フォント
	mLevelFont = mShimbashiGothicFont;
	if (mLevelFont == nullptr) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		success = false;
	}

	mBuffFont = mShimbashiGothicFont;
	if (mBuffFont == nullptr) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		success = false;
	}
	
	
	UpdateLevelText(); // レベルテキストの初期化

	// カードの初期化（バフカード用）
	Card::mScreenWidth = SCREEN_WIDTH;
	Card::mScreenHeight = SCREEN_HEIGHT;
	SDL_Color whiteColor = { 255, 255, 255, 255 }; // White color
	SDL_Color blueColor = { 0, 0, 255, 255 }; // Blue color

	// カードのテクスチャ作成
	mWhiteRectangleTexture = Card::CreateRectBorderTexture(mRenderer, mRectangleCard1.GetRect(), 2, whiteColor);
	mBlueRectangleTexture = Card::CreateRectBorderTexture(mRenderer, mRectangleCard1.GetRect(), 2, blueColor);
	// カードのx座標とy座標の初期化
	mRectangleCard1.Initialize( RECTANGLECARD1_POS_X, RECTANGLECARD1_POS_Y);
	mRectangleCard2.Initialize( RECTANGLECARD2_POS_X, RECTANGLECARD2_POS_Y);
	mRectangleCard3.Initialize( RECTANGLECARD3_POS_X, RECTANGLECARD3_POS_Y);
	// カードのテクスチャを設定
	mRectangleCard1.SetCardTexture(mWhiteRectangleTexture);
	mRectangleCard2.SetCardTexture(mWhiteRectangleTexture);
	mRectangleCard3.SetCardTexture(mWhiteRectangleTexture);
	// 詳細カードとアイコンカードのx座標とy座標の初期化
	mDetailCard1.Initialize(DETAILCARD1_POS_X, DETAILCARD1_POS_Y);
	mDetailCard2.Initialize(DETAILCARD2_POS_X, DETAILCARD2_POS_Y);
	mDetailCard3.Initialize(DETAILCARD3_POS_X, DETAILCARD3_POS_Y);
	// 詳細カードのテクスチャ作成
	mWhiteDetailTexture = Card::CreateRectBorderTexture(mRenderer, mDetailCard1.GetRect(), 2, whiteColor);
	// 詳細カードのテクスチャを設定
	mDetailCard1.SetCardTexture(mWhiteDetailTexture);
	mDetailCard2.SetCardTexture(mWhiteDetailTexture);
	mDetailCard3.SetCardTexture(mWhiteDetailTexture);
	// アイコンカードのx座標とy座標の初期化
	mIconCard1.Initialize( ICONCARD1_POS_X, ICONCARD1_POS_Y);
	mIconCard2.Initialize( ICONCARD2_POS_X, ICONCARD2_POS_Y);
	mIconCard3.Initialize( ICONCARD3_POS_X, ICONCARD3_POS_Y);
	// アイコンカードのテクスチャ作成
	mWhiteIconTexture = Card::CreateRectBorderTexture(mRenderer, mIconCard1.GetRect(), 2, whiteColor);
	// アイコンカードのテクスチャを設定
	mIconCard1.SetCardTexture(mWhiteIconTexture);
	mIconCard2.SetCardTexture(mWhiteIconTexture);
	mIconCard3.SetCardTexture(mWhiteIconTexture);
		
	return success;
}

//EXPバーの初期化
void Game::InitializeBar()
{
	mPlayer->ResetExp();
}

// レベルテキストの更新
void Game::UpdateLevelText() {
	if (mTextTexture != nullptr) {
		SDL_DestroyTexture(mTextTexture);
		mTextTexture = nullptr;
	}

	char textBuffer[32];	
	snprintf(textBuffer, sizeof(textBuffer), "Lv : %d", mPlayer->GetCurrentLevel() + 1);
	
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderUTF8_Solid(mLevelFont, textBuffer, textColor);
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, surface);

	mTextRect.w = surface->w;
	mTextRect.h = surface->h;

	SDL_FreeSurface(surface);
}

// 新たなバフをリストに追加する関数
void Game::AddBuffToList(BUFF_TYPE buffType)
{
	if(buffType == BUFF_TYPE_NONE || buffType == BUFF_TYPE_MAX)
	{
		return;
	}

	auto itPlayer = std::find_if(mPlayer->mBuffList.begin(), mPlayer->mBuffList.end(), [buffType](const BuffEntry& buff) {
		return buff.buffType == buffType;
		});

	if (itPlayer == mPlayer->mBuffList.end())
	{
		return;
	}

	char textBuffer[128];
	SDL_Color whiteColor = { 255, 255, 255, 255 };// White color
	std::string buffName = Loader::buffTypeToString(buffType);
	snprintf(textBuffer, sizeof(textBuffer), "%s x%d", buffName.c_str(), itPlayer->count);
	SDL_Texture* newTexture = getTextTexture(mRenderer, mBuffFont, textBuffer, whiteColor);

	auto it = std::find_if(mBuffTextures.begin(), mBuffTextures.end(), [buffType](BuffTextureData* data) {
		return data->buffType == buffType;
	});

	if(it != mBuffTextures.end())
	{
		// すでにバフがある場合は、テクスチャを更新
		if ((*it)->texture)
		{
			SDL_DestroyTexture((*it)->texture);
		}
		(*it)->texture = newTexture;
	}
	else
	{
		// バフがない場合は、新しいバフを追加
		int newIndex = static_cast<int>(mBuffTextures.size());
		BuffTextureData* buffTextureData = new BuffTextureData();
		buffTextureData->buffType = buffType;
		buffTextureData->texture = newTexture;
		buffTextureData->rect = { 150, 20 * newIndex, 120, 20 };
		mBuffTextures.push_back(buffTextureData);
	}
}


// フェーズの初期化
void Game::InitializePhase()
{
	mPhases.clear();
	// Initialize phase 1
	Phase phase1;
	phase1.phaseNumber = PHASE_1;
	phase1.spawnList.push_back({ ENEMY_TYPE_SHOOTERENEMY, 1, 1.0f, 0.0f }); // 10 apper every 1 seconds
	phase1.spawnList.push_back({ ENEMY_TYPE_SINSHOOTERENEMY, 1, 2.0f, 0.0f }); // 10 apper every 2 seconds
	phase1.spawnList.push_back({ ENEMY_TYPE_FOLLOWTARGETENEMY, 1, 1.0f, 0.0f }); // 10 apper every 1 seconds
	mPhases.push_back(phase1);
	/*
	// Initialize phase 2
	Phase phase2;
	phase2.phaseNumber = PHASE_2;
	phase2.spawnList.push_back({ ENEMY_TYPE_SHOOTERENEMY, 5, 1.5f, 0.0f }); // 10 apper every 1.5 seconds
	phase2.spawnList.push_back({ ENEMY_TYPE_ENEMY, 5, 4.0f, 0.0f }); // 5 apper every 4 seconds
	mPhases.push_back(phase2);

	// Initialize phase 3
	Phase phase3;
	phase3.phaseNumber = PHASE_3;
	phase3.spawnList.push_back({ ENEMY_TYPE_ENEMY, 5, 1.0f, 0.0f }); // 15 apper every 1 seconds
	phase3.spawnList.push_back({ ENEMY_TYPE_ENEMY, 5, 2.5f, 0.0f }); // 10 apper every 2.5 seconds
	mPhases.push_back(phase3);
	*/
}

// プレイヤーの作成
void Game::InitializePlayer()
{
	switch(mSelectedPlayerId)
	{
		case SIMPLEPLAYER_ID:
			mPlayer = std::make_unique<SimplePlayer>();
			break;
		case SPEEDPLAYER_ID:
			mPlayer = std::make_unique<SpeedPlayer>();
			break;
	default:
		break;
	}
}

// ゲームループ
void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

// 入力処理
void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
		}
		// マウスの座標を取得
		int mouseX = event.button.x;
		int mouseY = event.button.y;

		// カードの矩形を取得
		SDL_Rect cardRect1 = mRectangleCard1.GetRect();
		SDL_Rect cardRect2 = mRectangleCard2.GetRect();
		SDL_Rect cardRect3 = mRectangleCard3.GetRect();

		SDL_Point mousePoint = { mouseX, mouseY };

		// カーソルがカードの上にあるかどうかを判定
		if (SDL_PointInRect(&mousePoint, &cardRect1))
		{
			mIsCursolOnCard1 = true;
			mIsCursolOnCard2 = false;
			mIsCursolOnCard3 = false;
		} 
		else if(SDL_PointInRect(&mousePoint, &cardRect2))
		{
			mIsCursolOnCard1 = false;
			mIsCursolOnCard2 = true;
			mIsCursolOnCard3 = false;
		}
		else if(SDL_PointInRect(&mousePoint, &cardRect3))
		{
			mIsCursolOnCard1 = false;
			mIsCursolOnCard2 = false;
			mIsCursolOnCard3 = true;
		}
		else
		{
			mIsCursolOnCard1 = false;
			mIsCursolOnCard2 = false;
			mIsCursolOnCard3 = false;
		}

		// 左クリックでカードを選択
		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{

			if (SDL_PointInRect(&mousePoint, &cardRect1))
			{
				mBuff.applyBuff(mBuffList[0], mPlayer.get(), mBullets);
				AddBuffToList(mBuffList[0]);
				mIsRooleting = false;
			}
			if (SDL_PointInRect(&mousePoint, &cardRect2))
			{
				mBuff.applyBuff(mBuffList[1], mPlayer.get(), mBullets);
				AddBuffToList(mBuffList[1]);
				mIsRooleting = false;
			}

			if(SDL_PointInRect(&mousePoint, &cardRect3))
			{
				mBuff.applyBuff(mBuffList[2], mPlayer.get(), mBullets);
				AddBuffToList(mBuffList[2]);
				mIsRooleting = false;
			}
		}
	}

	// キーボードの状態を取得
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if(!mIsRooleting)
	{
		mPlayer->ProcessInput(keyState);
	}

}

// ゲームの更新処理
void Game::Update()
{
	if (mIsRooleting) {
		mTicksCount = SDL_GetTicks();
		return;
	}
	if (!mPlayer->IsActive())
	{
		SDL_Log("Player is destroyed. Game Over!");
		mIsRunning = false;
		mResult = RESULT::LOSE;
		return;
	}

	// 60 FPSを維持する
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mPlayer->Update(deltaTime);

	// 敵と弾の更新処理
	for (auto& bullet : mBullets)
	{
		bullet->Update(deltaTime);
	}

	for (auto& bullet : mEnemyBullets)
	{
		bullet->Update(deltaTime);
	}

	for (auto& enemy : mEnemies)
	{
		enemy->Update(deltaTime);
	}

	// プレイヤー弾の出現処理
	for (auto& b : mPlayer->GetBulletSpawnList())
	{
		b.currentSpawnTimer += deltaTime;
		if (b.currentSpawnTimer >= b.spawnInterval)
		{
			SpawnBullet(b.bulletType);
			b.currentSpawnTimer = 0.0f;
		}
	}

	// 敵出現処理
	Phase& currentPhase = mPhases[mCurrentPhaseIndex];
	for (auto& spwanData : currentPhase.spawnList)
	{
		if (spwanData.count > 0)
		{
			spwanData.currentSpawnTimer += deltaTime;
			if (spwanData.currentSpawnTimer >= spwanData.spawnInterval)
			{
				SpawnEnemy(spwanData.enemyType);
				spwanData.count--;
				spwanData.currentSpawnTimer = 0.0f;
			}
		}
	}

	// 敵弾の出現処理（mEnemiesを参照）
	for (auto& enemy : mEnemies)
	{
		if (!enemy->IsActive())
		{
			continue;
		}

		for (auto& spawnData : enemy->GetBulletSpawnList())
		{
			spawnData.currentSpawnTimer += deltaTime;
			if (spawnData.currentSpawnTimer >= spawnData.spawnInterval)
			{
				SpawnEnemyBullet(enemy.get(), spawnData.bulletType);
				spawnData.currentSpawnTimer = 0.0f;
			}
		}
	}

	// フェーズ完了判定
	if (std::all_of(currentPhase.spawnList.begin(), currentPhase.spawnList.end(), [](const EnemySpawnData& data) { return data.count <= 0; }))
	{
		if (mEnemies.empty())
		{
			SDL_Log("Phase %d completed!", currentPhase.phaseNumber);
			mCurrentPhaseIndex++;
			if (mCurrentPhaseIndex >= mPhases.size())
			{
				SDL_Log("All phases completed!");
				mIsRunning = false;
				mResult = RESULT::WIN;
			}
		}
	}



	// プレイヤー弾と敵の衝突判定
	for (auto& bullet : mBullets)
	{
		SDL_Rect bulletRect = bullet->GetRect();
		for (auto& enemy : mEnemies)
		{
			SDL_Rect enemyRect = enemy->GetRect();
			// 弾と敵の矩形が交差しているかを判定
			if (SDL_HasIntersection(&bulletRect, &enemyRect))
			{
				float dmg = mCalc.CalcDamage(mPlayer->status, enemy->status, bullet->status, mPlayer->GetCurrentLevel());
				enemy->status.health -= dmg;
				enemy->OnHit();

				bullet->Destroy();
				if (enemy->status.health <= 0)
				{
					mPlayer->AddExp(enemy->GetHaveExp());
					enemy->Destroy();
				}
				break;
			}
		}
	}

	// 敵弾とプレイヤーの衝突判定
	SDL_Rect& playerRect = mPlayer->GetRect();
	for (auto& bullet : mEnemyBullets)
	{
		SDL_Rect bulletRect = bullet->GetRect();
		
		// 弾とプレイヤーの矩形が交差しているかを判定
		if (SDL_HasIntersection(&bulletRect, &playerRect))
		{
			CalcDamageToPlayer(*mPlayer, *bullet);
			mPlayer->OnHit();
			mHpBar.Update(mPlayer->status.health, mPlayer->status.maxHealth);

			bullet->Destroy();
			if (mPlayer->status.health <= 0)
			{
				mPlayer->Destroy();
			}
		}
	}

	// プレイヤーと敵の衝突判定
	for (auto& enemy : mEnemies) 
	{
		SDL_Rect& enemyRect = enemy->GetRect();
		std::unique_ptr<SDL_Rect> rect = std::make_unique<SDL_Rect>(SDL_Rect{ 0, 0, 0, 0 });
		if(SDL_HasIntersection(&playerRect, &enemyRect) && SDL_IntersectRect(&playerRect, &enemyRect, rect.get())) 
		{	
			CheckCollisionBetweenPlayerAndEnemy(*mPlayer, *enemy, *rect);
			CalcHitDamageToPlayer(*mPlayer, *enemy);
			CalcHitDamageToEnemy(*mPlayer, *enemy);

			mPlayer->OnHit();
			enemy->OnHit();
			mHpBar.Update(mPlayer->status.health, mPlayer->status.maxHealth);

			if(enemy->status.health <= 0) 
			{
				mPlayer->AddExp(enemy->GetHaveExp());
				enemy->Destroy();
			}
		
			if (mPlayer->status.health <= 0) 
			{
				mPlayer->Destroy();
			}
		}
	}

	// レベルアップ処理
	if(mPlayer->GetExp() >= mPlayer->GetMaxExp()) 
	{
		mPlayer->SetExp(mPlayer->GetExp() - mPlayer->GetMaxExp());
		mPlayer->SetMaxExp(static_cast<LEVEL_NUMBER>(static_cast<int>(mPlayer->GetCurrentLevel()) + 1));
		mPlayer->SetNextLevel(mPlayer->GetCurrentLevel());		//プレイヤー自身のレベルを上げる 
		mPlayer->SetNextHp();									//プレイヤー自身のHPを上げる
		UpdateLevelText();										// レベルテキストの更新
		mIsRooleting = true;
		mBuffList.clear();
		for(int i = 0; i < 3; i++) 
		{
			mBuffList.push_back(mBuff.getRandomBuff(mPlayer.get()));
			SDL_Log("Buff %d: %d", i + 1, mBuffList[i]);
		}
	}

	// 経験値バーの更新
	mExpBar.Update(mPlayer->GetExp(), mPlayer->GetMaxExp());

	mBullets.erase(
		std::remove_if(mBullets.begin(), mBullets.end(), [](const auto& bullet) { return !bullet->IsActive() || bullet->IsOffScreen(); }),
		mBullets.end());

	mEnemyBullets.erase(
		std::remove_if(mEnemyBullets.begin(), mEnemyBullets.end(), [](const auto& bullet) { return !bullet->IsActive() || bullet->IsOffScreen(); }),
		mEnemyBullets.end());

	mEnemies.erase(
		std::remove_if(mEnemies.begin(), mEnemies.end(), [](const auto& enemy) { return !enemy->IsActive() || enemy->IsOffScreen(); }),
		mEnemies.end());

	
}

// 敵の出現処理
void Game::SpawnEnemy(ENEMY_TYPE enemyType)
{
	std::unique_ptr<Enemy> newEnemy = nullptr;
	switch (enemyType)
	{
	case ENEMY_TYPE_ENEMY:
	{
		newEnemy = std::make_unique<Enemy>();
		break;
	}
	case ENEMY_TYPE_FASTENEMY:
	{
		newEnemy = std::make_unique<FastEnemy>();
		break;
	}
	case ENEMY_TYPE_SHOOTERENEMY:
	{
		newEnemy = std::make_unique<ShooterEnemy>();
		break;
	}
	case ENEMY_TYPE_FOLLOWTARGETENEMY:
	{
		newEnemy = std::make_unique<FollowTargetEnemy>();
		break;
	}
	case ENEMY_TYPE_SINSHOOTERENEMY:
	{
		newEnemy = std::make_unique<SinShooterEnemy>();
		break;
	}
	default:
		break;
	}

	if (newEnemy)
	{
		newEnemy->SetTargetPlayer(mPlayer.get()); // プレイヤーへの参照を設定
		newEnemy->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT);
		mEnemies.push_back(std::move(newEnemy));
	}

	SDL_Log("Spawned enemy of type: %d", enemyType);
}

// プレイヤーの弾の出現処理
void Game::SpawnBullet(BULLET_TYPE bulletType)
{
	std::unique_ptr<Bullet> newBullet = nullptr;
	switch (bulletType)
	{
	case BULLET_TYPE_PLAYER_STRAIGHT:
	{
		newBullet = std::make_unique<P_StraightBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 0, 255)); // Yellow color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		break;
	}
	case BULLET_TYPE_PLAYER_BOTTOMLEFT:
	{
		newBullet = std::make_unique<P_BottomLeftBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 0, 255)); // Yellow color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		break;
	}
	case BULLET_TYPE_PLAYER_TOPRIGHT:
	{
		newBullet = std::make_unique<P_TopRightBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 0, 255)); // Yellow color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		break;
	}
	case BULLET_TYPE_PLAYER_TRIANGLE:
	{
		newBullet = std::make_unique<P_StraightBullet>();
		std::unique_ptr<Bullet> TopRight = std::make_unique<P_TopRightBullet>();
		std::unique_ptr<Bullet> BottomLeft = std::make_unique<P_BottomLeftBullet>();
		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, TopRight->GetWidth(), TopRight->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 255, 0, 255)); // Yellow color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);

		TopRight->Initialize(mTexture, SCREEN_WIDTH, SCREEN_HEIGHT, mPlayer->GetPosX(), mPlayer->GetPosY(), mPlayer->GetWidth(), mPlayer->GetHeight());
		BottomLeft->Initialize(mTexture, SCREEN_WIDTH, SCREEN_HEIGHT, mPlayer->GetPosX(), mPlayer->GetPosY(), mPlayer->GetWidth(), mPlayer->GetHeight());
		SDL_FreeSurface(surface);
		mBullets.push_back(std::move(TopRight));
		mBullets.push_back(std::move(BottomLeft));

		
		break;
	}

	default:
		break;
	}

	if (newBullet)
	{
		newBullet->Initialize(
			mTexture,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			mPlayer->GetPosX(),
			mPlayer->GetPosY(),
			mPlayer->GetWidth(),
			mPlayer->GetHeight()
		);

		mBullets.push_back(std::move(newBullet));
	}
}

// 敵の弾の出現処理
void Game::SpawnEnemyBullet(Enemy* shooterEnemy, BULLET_TYPE bulletType)
{
	if (shooterEnemy == nullptr || !shooterEnemy->IsActive())
	{
		return;
	}

	std::unique_ptr<Bullet> newBullet = nullptr;
	switch (bulletType)
	{
	case BULLET_TYPE_ENEMY_STRAIGHT:
	{
		newBullet = std::make_unique<E_StraightBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 0, 255)); // Red color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		break;
	}
	case BULLET_TYPE_ENEMY_BOTTOMLEFT:
	{
		newBullet = std::make_unique<E_BottomLeftBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 0, 255)); // Red color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		break;
	}
	case BULLET_TYPE_ENEMY_TOPRIGHT:
	{
		newBullet = std::make_unique<E_TopRightBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 0, 255)); // Red color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		break;
	}
	case BULLET_TYPE_ENEMY_TRIANGLE:
	{
		newBullet = std::make_unique<E_StraightBullet>();
		std::unique_ptr<Bullet> TopRight = std::make_unique<E_TopRightBullet>();
		std::unique_ptr<Bullet> BottomLeft = std::make_unique<E_BottomLeftBullet>();
		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, TopRight->GetWidth(), TopRight->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 0, 255)); // Red color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);

		TopRight->Initialize(mTexture, SCREEN_WIDTH, SCREEN_HEIGHT, mPlayer->GetPosX(), mPlayer->GetPosY(), mPlayer->GetWidth(), mPlayer->GetHeight());
		BottomLeft->Initialize(mTexture, SCREEN_WIDTH, SCREEN_HEIGHT, mPlayer->GetPosX(), mPlayer->GetPosY(), mPlayer->GetWidth(), mPlayer->GetHeight());
		SDL_FreeSurface(surface);
		mEnemyBullets.push_back(std::move(TopRight));
		mEnemyBullets.push_back(std::move(BottomLeft));

		break;
	}
	case BULLET_TYPE_ENEMY_SIN:
	{
		newBullet = std::make_unique<E_SinBullet>();

		SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, newBullet->GetWidth(), newBullet->GetHeight(), 32, SDL_PIXELFORMAT_RGBA32);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 0, 255)); // Red color
		mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		break;
	}
	default:
		break;
	}

	if (newBullet)
	{
		newBullet->Initialize(
			mTexture,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			static_cast<float>(shooterEnemy->GetRect().x),
			static_cast<float>(shooterEnemy->GetRect().y),
			shooterEnemy->GetRect().w,
			shooterEnemy->GetRect().h);
		mEnemyBullets.push_back(std::move(newBullet));
	}
}

// プレイヤーと敵の衝突判定
void Game::CheckCollisionBetweenPlayerAndEnemy(Player& player, Enemy& enemy, SDL_Rect& intersection)
{
	SDL_Rect playerRect = player.GetRect();
	SDL_Rect enemyRect = enemy.GetRect();

	float playerCenterX = playerRect.x + playerRect.w / 2.0f;
	float playerCenterY = playerRect.y + playerRect.h / 2.0f;
	float enemyCenterX = enemyRect.x + enemyRect.w / 2.0f;
	float enemyCenterY = enemyRect.y + enemyRect.h / 2.0f;

	float playerX = player.GetPosX();
	float playerY = player.GetPosY();
	float enemyX = enemy.GetPosX();
	float enemyY = enemy.GetPosY();
	
	// 衝突の方向に応じてプレイヤーと敵をノックバックさせる
	if (intersection.w >= intersection.h && playerCenterY < enemyCenterY)// プレイヤーが上
	{
		playerY -= (intersection.h + player.status.knockbackDistance);
		enemyY += (intersection.h + enemy.status.knockbackDistance);
		
	}
	else if (intersection.w >= intersection.h && playerCenterY > enemyCenterY)// プレイヤーが下
	{
		playerY += (intersection.h + player.status.knockbackDistance);
		enemyY -= (intersection.h + enemy.status.knockbackDistance);
	}
	else if(intersection.w <= intersection.h && playerCenterX < enemyCenterX)// プレイヤーが左
	{
		playerX -= (intersection.w + player.status.knockbackDistance);
		enemyX += (intersection.w + enemy.status.knockbackDistance);
	}
	else if (intersection.w <= intersection.h && playerCenterX > enemyCenterX)// プレイヤーが右
	{
		playerX += (intersection.w + player.status.knockbackDistance);
		enemyX -= (intersection.w + enemy.status.knockbackDistance);
	}

	player.SetPosition(playerX, playerY);
	enemy.SetPosition(enemyX, enemyY);
}

// 描画処理
void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	// プレイヤー、敵、弾の描画
	if (!mIsRooleting) {
		mPlayer->Render(mRenderer);

		for (auto& enemy : mEnemies)
		{
			enemy->Render(mRenderer);
		}

		for (auto& bullet : mBullets)
		{
			bullet->Render(mRenderer);
		}

		for (auto& bullet : mEnemyBullets)
		{
			bullet->Render(mRenderer);
		}

		for(auto& buffTextureData : mBuffTextures)
		{
			if (buffTextureData->texture) 
			{
				SDL_RenderCopy(mRenderer, buffTextureData->texture, NULL, &buffTextureData->rect);
			}
			else
			{
				SDL_Log("Buff texture is null for buff type: %d", buffTextureData->buffType);
			}
		}

		mExpBar.Render(mRenderer);
		mHpBar.Render(mRenderer);
		SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
	}
	else
	{
		// バフ選択画面の描画処理
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
		SDL_RenderClear(mRenderer);
		// カードの描画処理
		if (mIsCursolOnCard1) 
		{
			mRectangleCard1.SetCardTexture(mBlueRectangleTexture);
		}
		else 
		{
			mRectangleCard1.SetCardTexture(mWhiteRectangleTexture);
		}

		if (mIsCursolOnCard2)
		{
			mRectangleCard2.SetCardTexture(mBlueRectangleTexture);
		}
		else
		{
			mRectangleCard2.SetCardTexture(mWhiteRectangleTexture);
		}

		if (mIsCursolOnCard3)
		{
			mRectangleCard3.SetCardTexture(mBlueRectangleTexture);
		}
		else
		{
			mRectangleCard3.SetCardTexture(mWhiteRectangleTexture);
		}

		mRectangleCard1.Render(mRenderer);
		mRectangleCard2.Render(mRenderer);
		mRectangleCard3.Render(mRenderer);

		mDetailCard1.Render(mRenderer);
		mDetailCard2.Render(mRenderer);
		mDetailCard3.Render(mRenderer);

		mIconCard1.Render(mRenderer);
		mIconCard2.Render(mRenderer);
		mIconCard3.Render(mRenderer);

		// バフのテキストと画像の描画
		for(size_t i = 0; i < mBuffList.size(); i++)
		{
			mBuffTexture = mBuff.getBuffTexture(mBuffList[i], mBuffFont, mRenderer, mBuffTextRects[i], mPlayer.get());
			if (mBuffTexture) 
			{
				SDL_RenderCopy(mRenderer, mBuffTexture, NULL, &mBuffTextRects[i]);
				SDL_DestroyTexture(mBuffTexture);
				mBuffTexture = nullptr;
			}
			mBuffImageTexture = mBuff.getBuffImageTexture(mBuffList[i], mRenderer);
			if (mBuffImageTexture) 
			{
				SDL_RenderCopy(mRenderer, mBuffImageTexture, NULL, &mBuffImageRects[i]);
				SDL_DestroyTexture(mBuffImageTexture);
				mBuffImageTexture = nullptr;
			}
		}
	
	}

	SDL_RenderPresent(mRenderer);
}



