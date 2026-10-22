#pragma once

#define SDL_MAIN_HANDLED	
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../BaseWindow.h"
#include "../../card/cards/CharacterSelectCard.h"
#include "../../common/Type.h"

class Finish : public BaseWindow {
public:
   typedef enum {
		NEXT_ACTION_MENU,
		NEXT_ACTION_RETRY,
		NEXT_ACTION_EXIT
	}NEXT_ACTION;

	Finish();
	~Finish();

    NEXT_ACTION Main();

	bool Initialize() override;
	void RunLoop() override;
	void Shutdown() override;
	void SetResult(RESULT result) { mResult = result; }

private:
	void ProcessInput() override;
	void Update() override;
	void GenerateOutput() override;

	RESULT mResult;	
	TTF_Font* mFinishFont;

	//勝敗のテキスト
	SDL_Rect mTextRect;
	SDL_Texture* mTextTexture;

	//メニューに戻るカード・テキスト
	CharacterSelectCard mFinishCardRect;
	SDL_Texture* mFinishCardTexture;
	SDL_Rect mFinishCardTextRect;
	SDL_Texture* mFinishCardTextTexture;

	//再挑戦するときのカード・テキスト
	CharacterSelectCard mRetryCardRect;
	SDL_Texture* mRetryCardTexture;
	SDL_Rect mRetryCardTextRect;
	SDL_Texture* mRetryCardTextTexture;

	NEXT_ACTION mNextAction;

	bool mIsRunning;
}; 
