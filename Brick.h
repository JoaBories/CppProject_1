#pragma once

#include "raylib.h"

class Brick
{
private :
	Vector2 mPosition;
	int mLivesCount;
	int mColumn;
	int mRow;

public :
	static Vector2 mSize;
	static int mMaxLives;

	Brick();
	Brick(Vector2 position, int column, int row, int lives);
	~Brick();

	static void SetBrickSize(Vector2 size);

	void TakeDamage();

	bool IsAlive() const;
	Vector2 GetPosition() const;
	Vector2 GetSize() const;
	int GetLives() const;

	void Draw() const;
};

