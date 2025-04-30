#include "Ball.h"

void Ball::ResolveBorderCollision()
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

void Ball::ResolvePaddleCollision()
{
	if(mPosition.y > (mScreenPos.y + mScreenSize.y) / 2 && mDirection.y >= 0)
	{
		if (CheckAABB(mPaddlePtr->GetPosition(), mPaddlePtr->GetSize()))
		{
			Vector2 bounce = { mDirection.x, -mDirection.y };
			Vector2 paddleBounce = Utils::Normalize(Utils::Distance(mPosition, mPaddlePtr->GetPosition()));
		}
	}
}

bool Ball::CheckAABB(Vector2 position, Vector2 size) const
{
	bool test1 = mPosition.x - mRadius >= position.x + size.x / 2;
	bool test2 = mPosition.x + mRadius <= position.x - size.x / 2;
	bool test3 = mPosition.y - mRadius >= position.y + size.y / 2;
	bool test4 = mPosition.y + mRadius <= position.y - size.y / 2;

	if (test1 && test2 && test3 && test4)
	{
		return true;
	}

	return false;
}

Ball::Ball() :
mPosition{ 0,0 },
mSpeed{ 0 },
mDirection{ 0,0 },
mRadius{ 0 },
mScreenPos{ 0,0 },
mScreenSize{ 0,0 },
mPaddlePtr{ nullptr }
{
}

Ball::~Ball()
{
}

Ball::Ball(Vector2 startPos, float speed, float radius, Vector2 screenPosition, Vector2 screenSize, Paddle *paddle) :
mPosition{ startPos },
mSpeed{ speed },
mDirection{ 1,0.5f },
mRadius{ radius },
mScreenPos{ screenPosition },
mScreenSize{ screenSize },
mPaddlePtr{ paddle }
{
}

void Ball::Update()
{
	mPosition.x += mDirection.x * mSpeed * GetFrameTime();
	mPosition.y += mDirection.y * mSpeed * GetFrameTime();

	ResolveBorderCollision();
}

void Ball::Draw()
{
	DrawCircle(mPosition.x, mPosition.y, mRadius, WHITE);
}
