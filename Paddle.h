#pragma once
#include <raylib.h>

class Paddle
{
private:
	Vector2 mPosition;
	Vector2 mSize;
	float mSpeed;
	Vector2 mScreenSize;

public:
	Paddle();
	Paddle(Vector2 startPos, Vector2 paddleSize, float paddleSpeed, Vector2 screenSize);
	~Paddle();

	void Update();
	void Draw() const;

	Vector2 GetPosition() const { return mPosition; }
	Vector2 GetSize() const { return mSize; }
};

