#include "Ball.h"

#include <iostream>
using std::cout;
using std::endl;

void Ball::ResolveBorderCollision()
{
	if (mPosition.x - mRadius <= 0 && mDirection.x <= 0)
	{
		mDirection = { -mDirection.x, mDirection.y };
	}
	else if (mPosition.x + mRadius >= 0 + mScreenSize.x && mDirection.x >= 0)
	{
		mDirection = { -mDirection.x, mDirection.y };
	}

	if (mPosition.y - mRadius <= 0 && mDirection.y <= 0)
	{
		mDirection = { mDirection.x, -mDirection.y };
	}
	else if (mPosition.y + mRadius >= 0 + mScreenSize.y && mDirection.y >= 0)
	{
		mDirection = { mDirection.x, -mDirection.y };
	}
}

void Ball::ResolvePaddleCollision()
{
	if(mPosition.y > (mScreenSize.y) / 20 * 17)
	{
		if (CheckAABB(mPaddlePtr->GetPosition(), mPaddlePtr->GetSize()))
		{
			Vector2 bounce = { mDirection.x, -mDirection.y };
			Vector2 paddleBounce = Utils::Normalize(Utils::Distance(mPosition, mPaddlePtr->GetPosition()));
			mDirection = Utils::Normalize(Utils::Vector2Lerp(bounce, paddleBounce, 1));
		}
	}
}

void Ball::ResolveBrickWallCollision()
{
	int rStart = (mPosition.y / Brick::mSize.x) - 1;
	int rEnd = rStart+3;

	int cStart = (mPosition.x / Brick::mSize.y) - 1;
	int cEnd = cStart+3;

	for (int r = rStart; r < rEnd; r++)
	{
		if (r > mWallPtr->GetRows() - 1) 
		{
			break;
		}

		for (int c = cStart; c < cEnd; c++)
		{
			if (mAlreadyCollidedX && mAlreadyCollidedY)
			{
				return;
			}

			if (c > mWallPtr->GetColumns() - 1)
			{
				break;
			}
			ResolveBrickCollision(mWallPtr->GetBrickPtr(r, c));
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
			mDirection = { (!mAlreadyCollidedX) ? mDirection.x * normal.x : mDirection.x, (!mAlreadyCollidedY) ? mDirection.y * normal.y : mDirection.y };
			brick->TakeDamage();
			*mScorePtr += 1;
			if (normal.x == -1)
			{
				mAlreadyCollidedX = true;
			}
			if (normal.y == -1)
			{
				mAlreadyCollidedY = true;
			}
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
	Vector2 distance = Utils::Normalize(Utils::AbsDistance(mPosition, position));
	Vector2 result;

	if (Utils::Abs(distance.x - distance.y) >= 0.1)
	{
		if (distance.x > distance.y)
		{
			result = { -1, 1 };
		}
		else
		{
			result = { 1, -1 };
		}
	}
	else
	{
		result = { 1, 1 };
	}
	

	//if (distance.x < 0.7 && distance.x > -0.7) result.x = 1;
	//else result.x = -1;
	//if (distance.y < 0.7 && distance.y > -0.7) result.y = 1;
	//else result.y = -1;

	return result;
}

Ball::Ball() :
mPosition{ 0,0 },
mSpeed{ 0 },
mDirection{ 0,0 },
mRadius{ 0 },
mScreenSize{ 0,0 },
mPaddlePtr{ nullptr },
mWallPtr{ nullptr },
mScorePtr{ nullptr },
mAlreadyCollidedX{ false },
mAlreadyCollidedY{ false }
{
}

Ball::~Ball()
{
}

Ball::Ball(Vector2 startPos, float speed, float radius, Vector2 screenSize, Paddle *paddle, BrickWall* brick, int *score) :
mPosition{ startPos },
mSpeed{ speed },
mDirection{ Utils::Normalize( { 0.1, -1 } ) },
mRadius{ radius },
mScreenSize{ screenSize },
mPaddlePtr{ paddle },
mWallPtr{ brick },
mScorePtr{ score },
mAlreadyCollidedX{ false },
mAlreadyCollidedY{ false },
isLaunched{ false }
{
}

Vector2 Ball::GetPosition() const
{
	return mPosition;
}

void Ball::Update()
{
	cout << isLaunched << endl;

	if (isLaunched)
	{
		mAlreadyCollidedX = false;
		mAlreadyCollidedY = false;

		mPosition.x += mDirection.x * mSpeed * GetFrameTime();
		mPosition.y += mDirection.y * mSpeed * GetFrameTime();

		ResolvePaddleCollision();
		ResolveBorderCollision();

		ResolveBrickWallCollision();
	}
	else
	{
		if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))
		{
			isLaunched = true;
		}
	}
}

void Ball::Draw() const
{
	DrawCircle(mPosition.x, mPosition.y, mRadius, WHITE);
}
