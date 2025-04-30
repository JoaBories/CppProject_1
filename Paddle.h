#pragma once
#include <raylib.h>

class Paddle
{
private:
	Vector2 position;
	Vector2 size;
	float speed;
	Vector2 screenPos;
	Vector2 screenSize;

public:
	Paddle();
	Paddle(Vector2 startPos, Vector2 paddleSize, float paddleSpeed, Vector2 screenPos, Vector2 screenSize);
	~Paddle();

	void Update();
	void Draw() const;

	Vector2 GetPosition() const { return position; }
	Vector2 GetSize() const { return size; }
};

