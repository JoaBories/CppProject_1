#include "BrickWall.h"
#include "Utils.h"

BrickWall::BrickWall() :
mColumns{ 0 },
mRows{ 0 },
mScreenSize{ 0,0 },
mBricks{ vector<vector<Brick>>()}
{
}

BrickWall::BrickWall(int rows, int column, Vector2 screenSize) :
mColumns{ column },
mRows{ rows },
mScreenSize{ screenSize }
{
	Brick::SetBrickSize({ mScreenSize.x / 10, mScreenSize.x/ 10 });
	
	for (int r = 0; r < mRows; r++)
	{
		mBricks.push_back( {} );
		for (int c = 0; c < mColumns; c++)
		{
			Vector2 position = { Brick::mSize.x/2 + Brick::mSize.x * c, Brick::mSize.y / 2 + Brick::mSize.y * r };
			mBricks[r].push_back(Brick(position, c, r, 1));
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

int BrickWall::GetNumberOfBricks()
{
	int count = 0;

	for (vector<Brick> row : mBricks)
	{
		for (Brick brick : row)
		{
			if (brick.IsAlive())
			{
				count++;
			}
		}
	}

	return count;
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

void BrickWall::Print() const // for debugging
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
