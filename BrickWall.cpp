#include "BrickWall.h"
#include "Utils.h"

BrickWall::BrickWall() :
mColumns{ 10 },
mRows{ 5 },
mScreenSize{ 0,0 },
mBricks{ Brick() }
{
}

BrickWall::BrickWall(int plan[5][10], Vector2 screenSize) :
mColumns{ 10 },
mRows{ 5 },
mScreenSize{ screenSize }
{
	Brick::SetBrickSize({ screenSize.x / mColumns, screenSize.y / (mRows * 2) });
	
	for (size_t r = 0; r < mRows; r++)
	{
		for (size_t c = 0; c < mColumns; c++)
		{
			Vector2 position = { screenSize.x / mColumns * (c+1) - Brick::mSize.x/2, screenSize.y / (mRows * 2) * (r + 1) - Brick::mSize.y/2};
			mBricks[r][c] = Brick(position, c, r, plan[r][c]);
		}
	}

}

BrickWall::~BrickWall()
{
	
}

Brick* BrickWall::GetBrickPtr(int row, int column)
{
	return &mBricks[row][column];
}

int BrickWall::GetRows() const
{
	return mRows;
}

int BrickWall::GetColumns() const
{
	return mColumns;
}

void BrickWall::Draw() const
{
	for (size_t r = 0; r < mRows; r++)
	{
		for (size_t c = 0; c < mColumns; c++)
		{
			mBricks[r][c].Draw();
		}
	}
}

void BrickWall::Print() const
{
	for (size_t r = 0; r < mRows; r++)
	{
		for (size_t c = 0; c < mColumns; c++)
		{
			cout << mBricks[r][c].GetLives();
		}
		cout << endl;
	}
}
