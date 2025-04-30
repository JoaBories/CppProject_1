#include "Ball.h"

void Ball::CheckBorderCollision()
{
	if (mPosition.x - mRadius <= mScreenPos.x && mDirection.x <= 0)
	{
		mDirection = { -mDirection.x, mDirection.y };
	}
	else if (mPosition.x + mRadius >= mScreenPos.x + mScreenSize.x && mDirection.x >= 0)
	{
		mDirection = { -mDirection.x, mDirection.y };
	}

	if (mPosition.y - mRadius <= mScreenPos.y && mDirection.y <= 0)
	{
		mDirection = { mDirection.x, -mDirection.y };
	}
	else if (mPosition.y + mRadius >= mScreenPos.y + mScreenSize.y && mDirection.y >= 0)
	{
		mDirection = { mDirection.x, -mDirection.y };
	}
}

Ball::Ball() :
mPosition{ 0,0 },
mSpeed{ 0 },
mDirection{ 0,0 },
mRadius{ 0 },
mScreenPos{ 0,0 },
mScreenSize{ 0,0 }
{
}

Ball::~Ball()
{
}

Ball::Ball(Vector2 startPos, float speed, float radius, Vector2 screenPosition, Vector2 screenSize) :
mPosition{ startPos },
mSpeed{ speed },
mDirection{ 1,0.5f },
mRadius{ radius },
mScreenPos{ screenPosition },
mScreenSize{ screenSize }
{
}

void Ball::Update()
{
	mPosition.x += mDirection.x * mSpeed * GetFrameTime();
	mPosition.y += mDirection.y * mSpeed * GetFrameTime();

	CheckBorderCollision();
}

void Ball::Draw()
{
	DrawCircle(mPosition.x, mPosition.y, mRadius, WHITE);
}
