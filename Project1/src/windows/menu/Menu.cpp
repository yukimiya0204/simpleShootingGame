#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <SDL2/SDL.h>


#include "Menu.h"


namespace {
    const int SCREEN_WIDTH = 640;			// スクリーン画面幅
	const int SCREEN_HEIGHT = 480;			// スクリーン画面高さ

 const int MENU_CARD_POS_X = 75;			// スタートボタンx座標
	const int MENU_CARD_POS_Y = 250;			// スタートボタンy座標

    const int EXIT_CARD_POS_X = 325;			// ゲーム終了ボタンx座標
	const int EXIT_CARD_POS_Y = 250;			// ゲーム終了ボタンy座標

   const int TITLE_TEXT_POS_X = 100;			// タイトルテキストx座標
	const int TITLE_TEXT_POS_Y = 50;			// タイトルテキストy座標
	const int TITLE_TEXT_WIDTH = 400;			// タイトルテキスト幅
	const int TITLE_TEXT_HEIGHT = 100;			// タイトルテキスト高さ

	const int BLANK = 10;				//カードとテキストの余白
}

Menu::Menu()
	: mTitleTextTexture(nullptr)
	, mMenuTextTexture(nullptr)
	, mMenuTexture(nullptr)
	, mMenuFont(nullptr)
    , mExitTexture(nullptr)
	, mExitTextTexture(nullptr)
	, mExitFont(nullptr)
	, mMenuAction(MENU_ACTION_NONE)
	, mIsRunning(true)
{
	mMenuTextRect = { MENU_CARD_POS_X + BLANK, MENU_CARD_POS_Y + BLANK, 0, 0 };	
	mTitleTextRect = {TITLE_TEXT_POS_X, TITLE_TEXT_POS_Y, TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT};
	mExitTextRect = { EXIT_CARD_POS_X + BLANK, EXIT_CARD_POS_Y + BLANK, 0, 0 };
}

Menu::~Menu()
{
}

//メモリ開放
void Menu::Shutdown()
{
	mMenuCard.SetCardTexture(nullptr);
	
	SDL_DestroyTexture(mTitleTextTexture);
	mTitleTextTexture = nullptr;

	SDL_DestroyTexture(mMenuTexture);
	mMenuTexture = nullptr;
	SDL_DestroyTexture(mMenuTextTexture);
	mMenuTextTexture = nullptr;
	mMenuFont = nullptr;

	SDL_DestroyTexture(mExitTexture);
	mExitTexture = nullptr;
	SDL_DestroyTexture(mExitTextTexture);
	mExitTextTexture = nullptr;
	mExitFont = nullptr;
}

//初期化
bool Menu::Initialize()
{
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		success = false;
		return success;
	}
	// window作成
	mWindow = SDL_CreateWindow
	(
		"Menu", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT, 
		0
	);
	if(!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		success = false;
		return success;
	}

	// renderer作成
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if(mRenderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		success = false;
		return success;
	}

	// TTF初期化とフォント読み込み
	TTF_Init();
	mShimbashiGothicFont = TTF_OpenFont("assets/fonts/ShimbashiGothic/ShimbashiGothic-Regular.otf", 24);
	if (mShimbashiGothicFont == nullptr) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
	}

	//テキストの色
	SDL_Color whiteColor = { 255, 255, 255, 255 }; // White color
	//タイトルテキストテクスチャ作成
	mTitleTextTexture = getTextTexture(mRenderer, mShimbashiGothicFont, "Shooting Game", whiteColor);
	//スタートボタンのカード作成
	mMenuCard.Initialize(MENU_CARD_POS_X, MENU_CARD_POS_Y);
	mMenuTexture = Card::CreateRectBorderTexture(mRenderer, mMenuCard.GetRect(), 2, whiteColor );
	mMenuCard.SetCardTexture(mMenuTexture);
	//スタートボタンのテキスト作成
	mMenuTextRect = { MENU_CARD_POS_X + BLANK, MENU_CARD_POS_Y + BLANK, mMenuCard.GetRect().w - 2 * BLANK, mMenuCard.GetRect().h - 2 * BLANK };
	mMenuFont = mShimbashiGothicFont;
	mMenuTextTexture = getTextTexture(mRenderer, mMenuFont, "Start Game", whiteColor);
	//終了ボタンのカード作成
	mExitCard.Initialize(EXIT_CARD_POS_X, EXIT_CARD_POS_Y);
	mExitTexture = Card::CreateRectBorderTexture(mRenderer, mExitCard.GetRect(), 2, whiteColor);
	mExitCard.SetCardTexture(mExitTexture);
	//終了ボタンのテキスト作成
	mExitTextRect = { EXIT_CARD_POS_X + BLANK, EXIT_CARD_POS_Y + BLANK, mExitCard.GetRect().w - 2 * BLANK, mExitCard.GetRect().h - 2 * BLANK };
	mExitFont = mShimbashiGothicFont;
	mExitTextTexture = getTextTexture(mRenderer, mExitFont, "Exit Game", whiteColor);

	return success;
}

//メインループ
void Menu::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

//入力処理
void Menu::ProcessInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			mIsRunning = false;
		}

		int mouseX = event.button.x;
		int mouseY = event.button.y;

		SDL_Rect cardRect1 = mMenuCard.GetRect();
		SDL_Rect cardRect2 = mExitCard.GetRect();
		SDL_Point mousePoint = { mouseX, mouseY };

		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			if(SDL_PointInRect(&mousePoint, &cardRect1))
			{
				SDL_Log("Menu Card Clicked!");
				mMenuAction = MENU_ACTION_START;
				mIsRunning = false;
			}
			
			if(SDL_PointInRect(&mousePoint, &cardRect2))
			{
				SDL_Log("Exit Card Clicked!");
				mMenuAction = MENU_ACTION_EXIT;
				mIsRunning = false;
			}
		}
	}
}

void Menu::Update()
{
}

//描画処理
void Menu::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	//タイトル
	SDL_RenderCopy(mRenderer, mTitleTextTexture, NULL, &mTitleTextRect);
	
	//スタートボタンとテキスト
	mMenuCard.Render(mRenderer);
	SDL_RenderCopy(mRenderer, mMenuTextTexture, NULL, &mMenuTextRect);
	
	//終了ボタンとテキスト
	mExitCard.Render(mRenderer);
	SDL_RenderCopy(mRenderer, mExitTextTexture, NULL, &mExitTextRect);

	SDL_RenderPresent(mRenderer);
}

//メイン関数
Menu::MENU_ACTION Menu::Main()
{
	bool success = Initialize();
	if (success)
	{
		RunLoop();
	}
	Shutdown();
	return mMenuAction;
}











