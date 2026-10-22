#include "Bullet.h"

Bullet::Bullet()
	: mPosition(0.0f, 0.0f)
	, mElapsedTime(0.0f)   

	, mScreenWidth(0)
	, mScreenHeight(0)
	, mPlayerHeight(0)
	, name("")

	, mIsActive(true)
	, mTexture(nullptr)
{
	status = BulletStatus_Init();
	mRect = { 0, 0, status.width, status.height };
}

Bullet::~Bullet()
{
}

