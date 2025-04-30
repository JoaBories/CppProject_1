#include "Engine.h"

Engine::Engine() :
	mPaddle{ Paddle() },
	mBall{ Ball() },
	mScreenSize{ 0,0 }
{
}

Engine::~Engine()
{
}

void Engine::Init( Vector2 screenSize )
{
	mScreenSize = screenSize;
	mPaddle = Paddle({ mScreenSize.x / 2, mScreenSize.y / 10 * 9 }, {mScreenSize.x / 4, mScreenSize.y / 30}, 300, {0,0}, mScreenSize);
	mBall = Ball({ mScreenSize.x / 2, mScreenSize.y / 2 }, 200, 10, { 0,0 }, mScreenSize, &mPaddle);
}

void Engine::Update()
{
	mPaddle.Update();
	mBall.Update();
}

void Engine::Draw()
{
	mPaddle.Draw();
	mBall.Draw();
}
