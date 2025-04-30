#pragma once
#include "raylib.h"
#include "Paddle.h"
#include "Utils.h"

class Ball
{
private :
	Vector2 mPosition;
	
	float mSpeed;
	Vector2 mDirection;

	float mRadius;

	Vector2 mScreenPos;
	Vector2 mScreenSize;

	Paddle* mPaddlePtr;

	void ResolveBorderCollision();
	void ResolvePaddleCollision();
	bool CheckAABB(Vector2 position, Vector2 size) const;

public :
	Ball();
	~Ball();
	Ball(Vector2 startPos, float speed, float radius, Vector2 screenPosition, Vector2 screenSize, Paddle *paddle);

	void Update();
	void Draw();

};

