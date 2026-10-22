#include "BaseWindow.h"

SDL_Window* BaseWindow::mWindow = nullptr;
SDL_Renderer* BaseWindow::mRenderer = nullptr;
TTF_Font* BaseWindow::mShimbashiGothicFont = nullptr;

BaseWindow::BaseWindow()
{

}

// window, renderer, and font破棄
void BaseWindow::CleanupSDL()
{
	if (mRenderer != nullptr) {
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
	if (mWindow != nullptr) {
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
	}
	// Close font
	if (mShimbashiGothicFont != nullptr) {
		TTF_CloseFont(mShimbashiGothicFont);
		mShimbashiGothicFont = nullptr;
	}
	TTF_Quit();
	SDL_Quit();
}

//テキストのSDL_Textureを作成する関数
SDL_Texture* BaseWindow::getTextTexture(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, 0);
	if (surface == nullptr)
	{
		SDL_Log("Failed to create surface for text: %s", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

int BaseWindow::FixedWidth(int availableWidth, size_t count, int spaceWidth)
{
	int width;
	width = (availableWidth - (count - 1) * spaceWidth) / count;
	return width;
}

int BaseWindow::FixedHeight(int availableHeight, size_t count, int spaceHeight)
{
	int height;
	height = (availableHeight - (count - 1) * spaceHeight) / count;
	return height;
}