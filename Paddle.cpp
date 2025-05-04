#include "Paddle.h"

Paddle::Paddle() :
	mPosition{ 0,0 },
	mSize{ 0,0 },
	mSpeed{ 0 },
	mScreenSize{ 0,0 }
{
}

Paddle::~Paddle()
{
}

Paddle::Paddle(Vector2 startPos, Vector2 paddleSize, float paddleSpeed, Vector2 screenSize) :
	mPosition{ startPos },
	mSize{ paddleSize },
	mSpeed{ paddleSpeed },
	mScreenSize{ screenSize }
{
}

void Paddle::Update()
{
	if (IsKeyDown(KEY_LEFT) && mPosition.x - mSize.x / 2 > 0)
	{
		mPosition.x -= mSpeed * GetFrameTime();
	}
	if (IsKeyDown(KEY_RIGHT) && mPosition.x + mSize.x / 2 < mScreenSize.x)
	{
		mPosition.x += mSpeed * GetFrameTime();
	}
}

void Paddle::Draw() const
{

	float xCentered = mPosition.x - mSize.x / 2;
	float yCentered = mPosition.y - mSize.y / 2;

	DrawRectangle( xCentered, yCentered, mSize.x, mSize.y, WHITE);
}