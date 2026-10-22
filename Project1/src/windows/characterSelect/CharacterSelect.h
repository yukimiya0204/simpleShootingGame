#pragma once

#include <vector>

#include "../BaseWindow.h"
#include "../../card/cards/CharacterSelectCard.h"
#include "../../card/cards/PlayerSelectCard.h"
#include "../../common/Type.h"

class CharacterSelect : public BaseWindow
{
public:
	CharacterSelect();
	~CharacterSelect();

	PLAYER_ID Main();

	bool Initialize() override;
	void RunLoop() override;
	void Shutdown() override;
	PLAYER_ID GetSelectedPlayerId() const { return mSelectedPlayerId; }

private:
	void ProcessInput() override;
	void Update() override;
	void GenerateOutput() override;
	std::string GetPlayerText(PLAYER_ID playerId); // プレイヤー名取得
	

	struct PlayerCardInfo {
		PlayerSelectCard playerSelectCard;
		SDL_Texture* playerCardTexture = nullptr;
		SDL_Texture* playerTextTexture = nullptr;
		SDL_Rect playerTextRect;
		PLAYER_ID playerId;
	};

	std::vector<PLAYER_ID> mPlayerList;
	std::vector<PlayerCardInfo> mPlayerCardInfos;
	//SDL関連

	//キャラクターセレクトのテキストとカード
		//テキスト
		SDL_Texture* mTextTexture;
		SDL_Rect mTextRect;
		//カード
		SDL_Texture* mCardTexture;
		CharacterSelectCard mCharacterSelectCard1;

	//選択するプレイヤー
		//テキスト
		SDL_Texture* mPlayerTextTexture;
		SDL_Rect mPlayerTextRect;
		//カード
		SDL_Texture* mPlayerCardTexture;
		PlayerSelectCard mPlayerSelectCard1;
			
	//選択されたプレイヤーのID
	PLAYER_ID mSelectedPlayerId;
				
	//フォント関連
	TTF_Font* mFont;

	//ループフラグ
	bool mIsRunning;

	//利用可能な範囲(カード)
	int mPlayerCardAvailableWidth= 600;
	int mPlayerCardAvailableHeight = 200;
	int mSpaceWidth = 10;
	int mSpaceHeight = 5;
};