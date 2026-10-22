#pragma once

#define SDL_MAIN_HANDLED	
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "../BaseWindow.h"
#include "../../card/cards/MenuCard.h"

class Menu : public BaseWindow {
public:
	Menu();
	~Menu();

	typedef enum {
		MENU_ACTION_START,
		MENU_ACTION_EXIT,
		MENU_ACTION_NONE
	}MENU_ACTION;

	MENU_ACTION Main();

	bool Initialize() override;
	void RunLoop() override;
	void Shutdown() override;

private:
	void ProcessInput() override;
	void Update() override;
	void GenerateOutput() override;

	MENU_ACTION mMenuAction;
	//SDL関連
	//題名テキスト
	SDL_Texture* mTitleTextTexture;
	SDL_Rect mTitleTextRect;

	//スタートボタンのカード
	SDL_Texture* mMenuTexture;
	MenuCard mMenuCard;

	//スタートボタンのテキスト
	SDL_Rect mMenuTextRect;
	SDL_Texture* mMenuTextTexture;
	TTF_Font* mMenuFont;

	//exitカード
	SDL_Texture* mExitTexture;
	MenuCard mExitCard;

	//exitボタンのテキスト
	SDL_Rect mExitTextRect;
	SDL_Texture* mExitTextTexture;
	TTF_Font* mExitFont;

	bool mIsRunning;
};