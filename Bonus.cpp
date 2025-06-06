#include "Bonus.h"

Bonus::Bonus() :
	mPosition{ 0,0 },
	mRadius{ 0 },
	mSpeed{ 0 }
{
}

Bonus::Bonus(Vector2 startPos, float radius, float speed) :
	mPosition{ startPos },
	mRadius{ radius },
	mSpeed{ speed }
{
}

Bonus::~Bonus()
{
}

void Bonus::Update()
{
	mPosition.y += mSpeed * GetFrameTime();

	if (mPosition.y > GetScreenHeight())
	{
		mPosition.y = -mRadius;
		mPosition.x = GetRandomValue(0, GetScreenWidth());
	}
}

void Bonus::Draw() const
{
	DrawCircle(mPosition.x, mPosition.y, mRadius, GREEN);
}

Vector2 Bonus::GetPosition() const
{
	return mPosition;
}

bool Bonus::ResolvePaddleAABB(Vector2 position, Vector2 size) const
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


