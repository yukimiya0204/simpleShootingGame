#include "Finish.h"
#include "Finish.h"

namespace 
{
   const int SCREEN_WIDTH = 640;		// スクリーン画面幅
	const int SCREEN_HEIGHT = 480;	// スクリーン画面高さ
	const int FINISH_CARD_POS_X = 100;	// メニューに戻るボタンx座標
	const int FINISH_CARD_POS_Y = 250;	// メニューに戻るボタンy座標
	const int RETRY_CARD_POS_X = 340;	// 再挑戦ボタンx座標
	const int RETRY_CARD_POS_Y = 250;	// 再挑戦ボタンy座標
	const int TEXT_WIDTH = 200;		// この画面のテキスト幅
	const int TEXT_HEIGH = 100;		// この画面のテキスト高さ
	const int TEXT_BLANK = 20;		// カードとテキストの空白
}


Finish ::Finish()
	: mTextTexture(nullptr)
	, mFinishFont(nullptr)
   , mFinishCardTexture(nullptr)
	, mFinishCardTextTexture(nullptr)
	, mRetryCardTexture(nullptr)
	, mRetryCardTextTexture(nullptr)
	, mResult(RESULT::RESULT_MAX)
  , mNextAction(NEXT_ACTION_MENU)
	, mIsRunning(true)
{
}	

Finish::~Finish()
{
}


bool Finish::Initialize()
{
	bool success = true;

	// テキストフォントの初期化
	mFinishFont = mShimbashiGothicFont;
	if (mFinishFont == nullptr)
	{
		mFinishFont = TTF_OpenFont("assets/fonts/ShimbashiGothic/ShimbashiGothic-Regular.otf", 24);
        if (mFinishFont == nullptr)
		{
			SDL_Log("Failed to load font: %s", TTF_GetError());
			return false;
		}
	}

	// 結果のテキストテクスチャを作成
	std::string finishMessage = "none";
	if (mResult == RESULT::WIN)
	{
		finishMessage = "You Win!";
	}
	else if (mResult == RESULT::LOSE)
	{
		finishMessage = "Game over";
	}

	SDL_Color textColor = { 255, 255, 255, 255 }; // White color
	SDL_Surface* surface = TTF_RenderUTF8_Solid(mFinishFont, finishMessage.c_str(), textColor);
 if (surface == nullptr)
	{
		SDL_Log("Failed to create finish text surface: %s", TTF_GetError());
        return false;
	}
	mTextTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
 if (mTextTexture == nullptr)
	{
		SDL_Log("Failed to create finish text texture: %s", SDL_GetError());
		SDL_FreeSurface(surface);
        return false;
	}
 
	// テキストの位置を設定
	mTextRect.w = TEXT_WIDTH;
	mTextRect.h = TEXT_HEIGH;
	mTextRect.x = (SCREEN_WIDTH - mTextRect.w) / 2; // Center horizontally
	mTextRect.y = (SCREEN_HEIGHT - mTextRect.h) / 4; // Center vertically
	SDL_FreeSurface(surface);

	// メニューに戻るカードの初期化
	mFinishCardRect.Initialize(FINISH_CARD_POS_X, FINISH_CARD_POS_Y);
	mFinishCardTexture = Card::CreateRectBorderTexture(mRenderer, mFinishCardRect.GetRect(), 2, textColor);
	mFinishCardRect.SetCardTexture(mFinishCardTexture);
	
	// メニューに戻るカードのテキストの初期化
	mFinishCardTextRect = { FINISH_CARD_POS_X + TEXT_BLANK, FINISH_CARD_POS_Y + TEXT_BLANK, mFinishCardRect.GetRect().w - 2 * TEXT_BLANK, mFinishCardRect.GetRect().h - 2 * TEXT_BLANK };
	mFinishCardTextTexture = getTextTexture(mRenderer, mFinishFont, "Menu", textColor);
	
	//再挑戦カードの初期化
	mRetryCardRect.Initialize(RETRY_CARD_POS_X, RETRY_CARD_POS_Y);
	mRetryCardTexture = Card::CreateRectBorderTexture(mRenderer, mRetryCardRect.GetRect(), 2, textColor);
	mRetryCardRect.SetCardTexture(mRetryCardTexture);
	// 再挑戦カードのテキストの初期化
	mRetryCardTextRect = { RETRY_CARD_POS_X + TEXT_BLANK, RETRY_CARD_POS_Y + TEXT_BLANK, mRetryCardRect.GetRect().w - 2 * TEXT_BLANK, mRetryCardRect.GetRect().h - 2 * TEXT_BLANK };
	mRetryCardTextTexture = getTextTexture(mRenderer, mFinishFont, "Retry", textColor);

	return success;
}

// メインループ
void Finish::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

// メモリ開放
void Finish::Shutdown()
{
	if (mTextTexture)
	{
		SDL_DestroyTexture(mTextTexture);
		mTextTexture = nullptr;
	}
  if (mFinishCardTexture)
	{
		SDL_DestroyTexture(mFinishCardTexture);
		mFinishCardTexture = nullptr;
	}
	if (mFinishCardTextTexture)
	{
		SDL_DestroyTexture(mFinishCardTextTexture);
		mFinishCardTextTexture = nullptr;
	}
	if (mRetryCardTexture)
	{
		SDL_DestroyTexture(mRetryCardTexture);
		mRetryCardTexture = nullptr;
	}
	if (mRetryCardTextTexture)
	{
		SDL_DestroyTexture(mRetryCardTextTexture);
		mRetryCardTextTexture = nullptr;
	}
	mFinishFont = nullptr;
}

// 入力処理
void Finish::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
         mNextAction = NEXT_ACTION_EXIT;
			mIsRunning = false;
           break;
		}

		int mouseX = event.button.x;
		int mouseY = event.button.y;

		SDL_Point mousePoint = { mouseX, mouseY };

		if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Rect cardRect = mFinishCardRect.GetRect();
			if (SDL_PointInRect(&mousePoint, &cardRect))
			{
                mNextAction = NEXT_ACTION_MENU;
				mIsRunning = false;
				break;
			}

			SDL_Rect retryCardRect = mRetryCardRect.GetRect();
			if (SDL_PointInRect(&mousePoint, &retryCardRect))
			{
				mNextAction = NEXT_ACTION_RETRY;
				mIsRunning = false;
				break;
			}
		}
	}
}

void Finish::Update()
{
	// Update logic for the finish window can be added here
}

// 描画処理
void Finish::GenerateOutput()
{
	// Draw background color
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	//Draw the finish card
	mFinishCardRect.Render(mRenderer);
	SDL_RenderCopy(mRenderer, mFinishCardTextTexture, NULL, &mFinishCardTextRect);
  mRetryCardRect.Render(mRenderer);
	SDL_RenderCopy(mRenderer, mRetryCardTextTexture, NULL, &mRetryCardTextRect);
	// Draw the finish message
	if (mTextTexture)
	{
		SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
	}
	SDL_RenderPresent(mRenderer);
}

// メイン関数
Finish::NEXT_ACTION Finish::Main()
{
	bool success = Initialize();
	if (success)
	{
		RunLoop();
	}
	Shutdown();
   return mNextAction;
}

