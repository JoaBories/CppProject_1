#include "Engine.h"

#include <chrono>
using namespace std::chrono;

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
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 },
		{1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 }
	};

	mWall = BrickWall(tempPlan, screenSize);

	mPaddle = Paddle({ mScreenSize.x / 2, mScreenSize.y / 10 * 9 }, {mScreenSize.x / 8, mScreenSize.y / 30}, 600, {0,0}, mScreenSize);
	mBall = Ball({ mScreenSize.x / 2, mScreenSize.y / 2 }, 500, 10, { 0,0 }, mScreenSize, &mPaddle, &mWall);

	mWall.Print();
}

void Engine::Update()
{
	mPaddle.Update();

	auto start = high_resolution_clock::now();
	mBall.Update();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start).count();
	std::cout << "Ball Update Time: " << duration << " microseconds" << std::endl;

}

void Engine::Draw() const
{
	mWall.Draw();
	mPaddle.Draw();
	mBall.Draw();
}
