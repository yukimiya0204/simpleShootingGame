#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class BaseWindow {
public:
	BaseWindow();

   static void CleanupSDL(); // SDL終了処理


	virtual bool Initialize() = 0;
	virtual void RunLoop() = 0;
	virtual void Shutdown() = 0;

   int FixedWidth(int availableWidth, size_t count, int spaceWidth); // 横幅を均等計算
	int FixedHeight(int availableHeight, size_t count, int spaceHeight); // 高さを均等計算


protected:
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void GenerateOutput() = 0;

  virtual SDL_Texture* getTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color); // 文字テクスチャ生成
	// SDL関連
	static SDL_Window* mWindow;
	static SDL_Renderer* mRenderer;

	static TTF_Font* mShimbashiGothicFont;
};