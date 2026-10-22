#include "windows/menu/Menu.h"
#include "windows/characterSelect/CharacterSelect.h"
#include "windows/game/Game.h"
#include "windows/finish/Finish.h"

int main(int argc, char* argv[])
{
    bool appRunning = true;

	while (appRunning)
	{
		//メインメニュー
		bool menuRunning = true;
		while (menuRunning)
		{
			Menu::MENU_ACTION action = Menu().Main();
			if(action == Menu::MENU_ACTION_START)
			{
				menuRunning = false;
			}
			else if(action == Menu::MENU_ACTION_EXIT)
			{
				return 0;
			}
		}
	;
		//キャラクターセレクト
		PLAYER_ID selectedPlayerId = CharacterSelect().Main();
		if (selectedPlayerId == PLAYER_ID_MAX) return 0;

		//ゲーム本体
		bool backToMenu = false;
		while (!backToMenu && appRunning)
		{
			//プレイ画面の処理
			Game game;
			game.SetSelectedPlayerId(selectedPlayerId);

			bool success = game.Initialize();

			if (success)
			{
				game.RunLoop();
			}
			game.Shutdown();
			//ゲーム終了後の処理
			Finish finish;
			finish.SetResult(game.getResult());
			Finish::NEXT_ACTION action = finish.Main();

			if (action == Finish::NEXT_ACTION_RETRY)
			{
				continue;
			}

			if (action == Finish::NEXT_ACTION_MENU)
			{
				backToMenu = true;
			}
			else
			{
				appRunning = false;
			}
		}

		BaseWindow::CleanupSDL();
	}
	return 0;	
}
