#pragma once
#include "Brick.h"

class BrickWall
{
private : 
	int mColumns;
	int mRows;
	Vector2 mScreenSize;
	Brick mBricks[5][10];

public :
	BrickWall();
	BrickWall(int plan[5][10], Vector2 screenSize, int gapSize);
	~BrickWall();

	//Brick* GetBrickPtr(int row, int column);
	//int GetNumberOfBricks();

	void Draw() const;

	void Print() const;
};

