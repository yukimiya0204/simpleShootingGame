#pragma once

#include <SDL2/SDL.h>
#include "../common/Vector.h"
#include "BulletStatus.h"

class Bullet {
public:

	BulletStatus status;
	std::string name; // ’e‚Ì–¼‘O
	Bullet();
	virtual ~Bullet();


	virtual void Initialize(SDL_Texture* texture, int screenWidth, int screenHeight, float playerPosX, float playerPosY,
		int playerWidth, int playerHeight) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;

	virtual inline bool IsOffScreen() const { return mPosition.x > mScreenWidth || mPosition.x < 0; }

	inline const SDL_Rect& GetRect() const { return mRect; }
	inline const int GetWidth() const { return mRect.w; }
	inline const int GetHeight() const { return mRect.h; }

	inline float GetBulletPower() const { return status.power; }
	inline float GetSpeed() const { return status.speed; }

	inline const bool IsActive() const { return mIsActive; }
	inline void Destroy() { mIsActive = false; }

	inline float GetElapsedTime() const { return mElapsedTime; }
	inline void ResetElapsedTime() { mElapsedTime = 0.0f; }

	inline double deg2rad(double degrees) {
		return degrees * (3.14159265358979323846 / 180.0);
	}

protected:

	SDL_Rect mRect;
	Vector2 mPosition;
	SDL_Texture* mTexture;
	
	float mElapsedTime; //Œo‰ßŽžŠÔ

	int mScreenWidth;
	int mScreenHeight;
	int mPlayerHeight;
	bool mIsActive;

};