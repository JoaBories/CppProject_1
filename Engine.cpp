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

	Brick::SetBrickSize({ 50,25 });

	int tempPlan[5][10]{
		{1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10},
		{2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11},
		{3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12},
		{4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,13},
		{5 ,6 ,7 ,8 ,9 ,10,11,12,13,14}
	};

	mWall = BrickWall(tempPlan, screenSize, 6);

	mPaddle = Paddle({ mScreenSize.x / 2, mScreenSize.y / 10 * 9 }, {mScreenSize.x / 8, mScreenSize.y / 30}, 600, {0,0}, mScreenSize);
	mBall = Ball({ mScreenSize.x / 2, mScreenSize.y / 2 }, 500, 10, { 0,0 }, mScreenSize, &mPaddle, &mWall);

	mWall.Print();
}

void Engine::Update()
{
	mPaddle.Update();
	mBall.Update();
}

void Engine::Draw() const
{
	mWall.Draw();
	mPaddle.Draw();
	mBall.Draw();
}
