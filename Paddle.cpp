#include "Paddle.h"

Paddle::Paddle() :
	position{ 0,0 },
	size{ 0,0 },
	speed{ 0 },
	screenPos{ 0,0 },
	screenSize{ 0,0 }
{
}

Paddle::~Paddle()
{
}

Paddle::Paddle(Vector2 startPos, Vector2 paddleSize, float paddleSpeed, Vector2 screenPos, Vector2 screenSize) :
	position{ startPos },
	size{ paddleSize },
	speed{ paddleSpeed },
	screenPos{ screenPos },
	screenSize{ screenSize }
{
}

void Paddle::Update()
{
	if (IsKeyDown(KEY_LEFT) && position.x - size.x / 2 > screenPos.x)
	{
		position.x -= speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_RIGHT) && position.x + size.x / 2 < screenPos.x + screenSize.x)
	{
		position.x += speed * GetFrameTime();
	}
}

void Paddle::Draw()
{

	float xCentered = position.x - size.x / 2;
	float yCentered = position.y - size.y / 2;

	DrawRectangle( xCentered, yCentered, size.x, size.y, WHITE);
}