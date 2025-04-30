#include "Ball.h"

#include <iostream>
using std::cout;
using std::endl;

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
	if(mPosition.y > (mScreenPos.y + mScreenSize.y) / 20 * 17 /*&& mDirection.y >= 0*/)
	{
		if (CheckAABB(mPaddlePtr->GetPosition(), mPaddlePtr->GetSize()))
		{
			Vector2 bounce = { mDirection.x, -mDirection.y };
			Vector2 paddleBounce = Utils::Normalize(Utils::Distance(mPosition, mPaddlePtr->GetPosition()));
			mDirection = Utils::Normalize(Utils::Vector2Lerp(bounce, paddleBounce, 1));
		}
	}
}

void Ball::ResolveBrickCollision(Brick *brick)
{
	if (brick->IsAlive()) 
	{
		if (CheckAABB(brick->GetPosition(), brick->GetSize()))
		{
			Vector2 normal = GetCollisionAxis(brick->GetPosition(), brick->GetSize());
			mDirection = { mDirection.x * normal.x, mDirection.y * normal.y };
			brick->TakeDamage();
		}
	}
}

bool Ball::CheckAABB(Vector2 position, Vector2 size) const
{
	bool test1 = mPosition.x - mRadius >= position.x + size.x / 2;
	bool test2 = mPosition.x + mRadius <= position.x - size.x / 2;
	bool test3 = mPosition.y - mRadius >= position.y + size.y / 2;
	bool test4 = mPosition.y + mRadius <= position.y - size.y / 2;

	if (test1 || test2 || test3 || test4)
	{
		return false;
	}

	return true;
}

Vector2 Ball::GetCollisionAxis(Vector2 position, Vector2 size) const
{
	Vector2 distance = Utils::Distance(mPosition, position);
	Vector2 overlap = { size.x / 2 + mRadius - distance.x, size.y / 2 + mRadius - distance.y };

	if (overlap.x < overlap.y)
	{
		return { 1,-1 };
	}
	else
	{
		return { -1,1 };
	}
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

Ball::Ball(Vector2 startPos, float speed, float radius, Vector2 screenPosition, Vector2 screenSize, Paddle *paddle, BrickWall* brick) :
mPosition{ startPos },
mSpeed{ speed },
mDirection{ Utils::Normalize( { 0.1, 1 } ) },
mRadius{ radius },
mScreenPos{ screenPosition },
mScreenSize{ screenSize },
mPaddlePtr{ paddle },
mWallPtr{ brick }
{
}

void Ball::Update()
{
	mPosition.x += mDirection.x * mSpeed * GetFrameTime();
	mPosition.y += mDirection.y * mSpeed * GetFrameTime();

	ResolvePaddleCollision();
	ResolveBorderCollision();
}

void Ball::Draw() const
{
	DrawCircle(mPosition.x, mPosition.y, mRadius, WHITE);
}
