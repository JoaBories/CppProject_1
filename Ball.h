#pragma once
#include "raylib.h"

class Ball
{
private :
	Vector2 mPosition;
	
	float mSpeed;
	Vector2 mDirection;

	float mRadius;

	Vector2 mScreenPos;
	Vector2 mScreenSize;

	void CheckBorderCollision();

public :
	Ball();
	~Ball();
	Ball(Vector2 startPos, float speed, float radius, Vector2 screenPosition, Vector2 screenSize);

	void Update();
	void Draw();

};

