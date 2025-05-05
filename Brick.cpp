#include "Brick.h"
#include "Utils.h"

Vector2 Brick::mSize = { 0,0 };
int Brick::mMaxLives = 0;

Brick::Brick() :
mPosition{ 0,0 },
mLivesCount{ 0 },
mColumn{ 0 },
mRow{ 0 }
{
}

Brick::Brick(Vector2 position, int column, int row, int lives) :
mLivesCount{ lives },
mColumn{ column },
mRow{ row },
mPosition{ position }
{
	if (lives > mMaxLives) 
	{
		mMaxLives = lives;
	}
}

Brick::~Brick()
{
}

void Brick::SetBrickSize(Vector2 size)
{
	mSize = size;
}

void Brick::TakeDamage()
{
	mLivesCount = (mLivesCount-1 < 0) ? 0 : mLivesCount-1;
}

bool Brick::IsAlive() const
{
	return mLivesCount > 0;
}

Vector2 Brick::GetPosition() const
{
	return mPosition;
}

Vector2 Brick::GetSize() const
{
	return mSize;
}

int Brick::GetLives() const
{
	return mLivesCount;
}

void Brick::Draw() const
{
	if (mLivesCount > 0)
	{
		float xCentered = mPosition.x - mSize.x / 2;
		float yCentered = mPosition.y - mSize.y / 2;

		Color fullLife;
		Color noLife;

		if ((mRow + mColumn) % 2 == 0)
		{
			fullLife = ColorFromNormalized({ 1,1,1,1 });
			noLife = ColorFromNormalized({ 0,0,0,1 });
		}
		else
		{
			fullLife = ColorFromNormalized({ 0.3,0.3,0.8,1 });
			noLife = ColorFromNormalized({ 0,0,0,1 });
		}
		
		float blend = (float) mLivesCount / mMaxLives;

		DrawRectangle(xCentered, yCentered, mSize.x - 4, mSize.y - 4, Utils::ColorLerp(noLife, fullLife, blend));
	}
}
