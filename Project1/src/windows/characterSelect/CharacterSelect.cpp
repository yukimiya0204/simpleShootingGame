#include "CharacterSelect.h"

//-------------------------------------------------------------
//Character Select Screen
//-------------------------------------------------------------
//select simple player or speed player
//--------------------------------------------------------------




namespace {
   const int SCREEN_WIDTH = 640;						// スクリーン幅
	const int SCREEN_HEIGHT = 480;					// スクリーン高さ

    const int CHARACTER_SELECT_CARD_POS_X = 220;			// キャラクターセレクトカードx座標
	const int CHARACTER_SELECT_CARD_POS_Y = 50;			// キャラクターセレクトカードy座標

   const int CHARACTER_SELECT_CARD_TEXT_POS_X = CHARACTER_SELECT_CARD_POS_X;	// プレイヤー名テキストx座標
	const int CHARACTER_SELECT_CARD_TEXT_POS_Y = CHARACTER_SELECT_CARD_POS_Y;	// プレイヤー名テキストy座標
	const int CHARACTER_SELECT_CARD_TEXT_WIDTH = 200;					// プレイヤー名テキスト幅
	const int CHARACTER_SELECT_CARD_TEXT_HEIGHT = 100;					// プレイヤー名テキスト高さ

    const int PLAYER_SELECT_CARD_POS_X = 20;				// プレイヤーセレクトx座標
	const int PLAYER_SELECT_CARD_POS_Y = 240;				// プレイヤーセレクトy座標
}

CharacterSelect::CharacterSelect()
	: mTextTexture(nullptr)
	, mCardTexture(nullptr)
	, mPlayerTextTexture(nullptr)
	, mPlayerCardTexture(nullptr)
	, mFont(nullptr)
	, mSelectedPlayerId(PLAYER_ID_MAX)
	, mIsRunning(true)
{
	mTextRect = 
	{ 
		CHARACTER_SELECT_CARD_TEXT_POS_X, 
		CHARACTER_SELECT_CARD_TEXT_POS_Y, 
		CHARACTER_SELECT_CARD_TEXT_WIDTH, 
		CHARACTER_SELECT_CARD_TEXT_HEIGHT 
	};

	mPlayerList = { SIMPLEPLAYER_ID, SPEEDPLAYER_ID };

	mPlayerTextRect = 
	{ 
		PLAYER_SELECT_CARD_POS_X,
		PLAYER_SELECT_CARD_POS_Y,
		FixedWidth(mPlayerCardAvailableWidth, mPlayerList.size(), mSpaceWidth),
		FixedHeight(mPlayerCardAvailableHeight, mPlayerList.size(), mSpaceHeight)
	};
}

CharacterSelect::~CharacterSelect()
{
}

// 
void CharacterSelect::Shutdown()
{
	mCharacterSelectCard1.SetCardTexture(nullptr);

	SDL_DestroyTexture(mCardTexture);
	mCardTexture = nullptr;

	SDL_DestroyTexture(mPlayerCardTexture);
	mPlayerCardTexture = nullptr;

	SDL_DestroyTexture(mTextTexture);
	mTextTexture = nullptr;

	SDL_DestroyTexture(mPlayerTextTexture);
	mPlayerTextTexture = nullptr;

	mFont = nullptr;
}

bool CharacterSelect::Initialize()
{
	bool success = true;

	mFont = mShimbashiGothicFont;
	SDL_Color whiteColor = { 255, 255, 255, 255 }; // White color

	mCharacterSelectCard1.Initialize(CHARACTER_SELECT_CARD_POS_X, CHARACTER_SELECT_CARD_POS_Y);
	mCardTexture = Card::CreateRectBorderTexture(mRenderer, mCharacterSelectCard1.GetRect(), 2, whiteColor);
	mCharacterSelectCard1.SetCardTexture(mCardTexture);

	mTextTexture = getTextTexture(mRenderer, mFont, "Character Select", whiteColor);

	mPlayerCardInfos.resize(mPlayerList.size());
	for(int i = 0; i < mPlayerList.size(); ++i)
	{
		int x = PLAYER_SELECT_CARD_POS_X + mPlayerTextRect.w * i + mSpaceWidth * i;
		int y = PLAYER_SELECT_CARD_POS_Y;

		mPlayerCardInfos[i].playerSelectCard.SetRect(x, y, mPlayerTextRect.w, mPlayerTextRect.h);

		mPlayerCardInfos[i].playerCardTexture = Card::CreateRectBorderTexture(
			mRenderer, mPlayerCardInfos[i].playerSelectCard.GetRect(), 2, whiteColor);

		mPlayerCardInfos[i].playerSelectCard.SetCardTexture(mPlayerCardInfos[i].playerCardTexture);
		mPlayerCardInfos[i].playerId = mPlayerList[i];
		mPlayerCardInfos[i].playerTextTexture = getTextTexture(mRenderer, mFont, GetPlayerText(mPlayerList[i]), whiteColor);
		mPlayerCardInfos[i].playerTextRect = { x, y, mPlayerTextRect.w, mPlayerTextRect.h };
	}
	
	return success;
}

void CharacterSelect::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

void CharacterSelect::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mSelectedPlayerId = PLAYER_ID_MAX;
			mIsRunning = false;
		}
		
		int mouseX = event.button.x;
		int mouseY = event.button.y;

		SDL_Point mousePoint = { mouseX, mouseY };

		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			for(int i = 0 ; i < mPlayerCardInfos.size(); ++i)
			{
				SDL_Rect cardRect = mPlayerCardInfos[i].playerSelectCard.GetRect();
				if (SDL_PointInRect(&mousePoint, &cardRect))
				{
					SDL_Log("Player Select Card Clicked! Player ID: %d", mPlayerCardInfos[i].playerId);
					mSelectedPlayerId = mPlayerCardInfos[i].playerId;
					mIsRunning = false;
					break;
				}
			}
		}
	}
}

void CharacterSelect::Update()
{
	// Update logic for character select window can be added here
}

void CharacterSelect::GenerateOutput()
{
	// Draw background color
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	// Draw cards and character select text
	mCharacterSelectCard1.Render(mRenderer);
	SDL_RenderCopy(mRenderer, mTextTexture, NULL, &mTextRect);
	
	for(auto& pci : mPlayerCardInfos)
	{
		pci.playerSelectCard.Render(mRenderer);
		SDL_RenderCopy(mRenderer, pci.playerTextTexture, NULL, &pci.playerTextRect);
	}

	SDL_RenderPresent(mRenderer);
}

std::string CharacterSelect::GetPlayerText(PLAYER_ID playerId)
{
	switch (playerId)
	{
	case SIMPLEPLAYER_ID:
		return "Simple Player";
	case SPEEDPLAYER_ID:
		return "Speed Player";
	default:
		return "Unknown Player";
	}
}

PLAYER_ID CharacterSelect::Main()
{
	CharacterSelect characterSelect;
	bool characterSelectSuccess = characterSelect.Initialize();
	if (characterSelectSuccess)
	{
		characterSelect.RunLoop();
	}
	characterSelect.Shutdown();
	PLAYER_ID selectedPlayerId = characterSelect.GetSelectedPlayerId();

	if (selectedPlayerId == PLAYER_ID_MAX)
	{
		BaseWindow::CleanupSDL();
	}
	return selectedPlayerId;
}


