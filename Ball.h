#pragma once
#include "raylib.h"
#include "Paddle.h"
#include "Brick.h"
#include "BrickWall.h"
#include "Utils.h"

class Ball
{
private :
	Vector2 mPosition;
	
	float mSpeed;
	Vector2 mDirection;

	float mRadius;

	Vector2 mScreenSize;

	Paddle* mPaddlePtr;

	BrickWall* mWallPtr;

	int* mScorePtr;

	bool mAlreadyCollidedX;
	bool mAlreadyCollidedY;

	bool mIsLaunched;
	Vector2 mTryBonus;

	void ResolveBorderCollision();
	void ResolvePaddleCollision();
	void ResolveBrickWallCollision();
	void ResolveBrickCollision(Brick *brick);
	bool CheckAABB(Vector2 position, Vector2 size) const;
	Vector2 GetCollisionAxis(Vector2 position, Vector2 size) const;

public :
	Ball();
	~Ball();
	Ball(Vector2 startPos, float speed, float radius, Vector2 screenSize, Paddle *paddle, BrickWall *brick, int *score);

	Vector2 GetPosition() const;

	Vector2 GetTryBonus() const;
	void ResetTryBonus();

	void Launch();

	void Update();
	void Draw() const;

};

