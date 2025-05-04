#pragma once
#include "Brick.h"
#include <vector>
using std::vector;

class BrickWall
{
private : 
	int mColumns;
	int mRows;
	Vector2 mScreenSize;
	vector<vector<Brick>> mBricks;

public :
	BrickWall();
	BrickWall(int rows, int column, Vector2 screenSize);
	~BrickWall();

	Brick* GetBrickPtr(int row, int column);
	int GetNumberOfBricks();

	int GetRows() const;
	int GetColumns() const;

	void Draw() const;

	void Print() const; // for debugging
};

