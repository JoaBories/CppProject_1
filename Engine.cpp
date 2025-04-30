#include "Engine.h"

Engine::Engine() :
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
	mBall = Ball({ mScreenSize.x / 2, mScreenSize.y / 2 }, 200, 10, { 0,0 }, mScreenSize);
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
