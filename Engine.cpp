#include "Engine.h"

#include <chrono>
using namespace std::chrono;

Engine::Engine() :
	mPaddle{ Paddle() },
	mBall{ Ball() },
	mScreenSize{ 0,0 },
	mPaddlePos{ 0,0 },
	mPaddleSize{ 0,0 },
	mPaddleSpeed{ 0 },
	mBallPos{ 0,0 },
	mBallSpeed{ 0 },
	mBallRadius{ 0 },
	mYLoosePosition{ 0 },
	mWall{ BrickWall() },
	mGameState{ Start }
{
}

Engine::~Engine()
{
}

void Engine::Init( Vector2 screenSize )
{
	mScreenSize = screenSize;

	mPaddlePos = { mScreenSize.x / 2, mScreenSize.y / 10 * 9 };
	mPaddleSize = { mScreenSize.x / 4, mScreenSize.y / 60 };
	mPaddleSpeed = 500;

	mBallPos = { mScreenSize.x / 2, mScreenSize.y / 20 * 17 };
	mBallSpeed = 500;
	mBallRadius = 8;

	mYLoosePosition = mScreenSize.y / 20 * 19;

	Brick::SetBrickSize({ 50,25 });

	mWall = BrickWall( 5, 10, mScreenSize );

	mPaddle = Paddle( mPaddlePos, mPaddleSize, mPaddleSpeed, mScreenSize);
	mBall = Ball( mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall);

	cout << mPaddle.GetPosition().x << " " << mPaddle.GetPosition().y << endl;
}

void Engine::Update()
{
	switch (mGameState)
	{
	case GameState::Start:
		if (IsKeyPressed(KEY_SPACE))
		{
			mGameState = GameState::Play;
		}

		mPaddle.Update();

		break;

	case GameState::Play:
		mPaddle.Update();
		mBall.Update();

		if (mWall.GetNumberOfBricks() == 0)
		{
			Win();
		}

		if (mBall.GetPosition().y >= mYLoosePosition)
		{
			Loose();
		}
		break;

	case GameState::Loose:
		if (IsKeyPressed(KEY_SPACE))
		{
			mGameState = GameState::Play;
		}

		mPaddle.Update();
		break;

	case GameState::Win:
		if (IsKeyPressed(KEY_SPACE))
		{
			mGameState = GameState::Play;
		}

		mPaddle.Update();
		break;
	}
	
}

void Engine::Draw() const
{
	switch (mGameState)
	{
	case GameState::Start:
		Utils::DrawTextCentered("BrickBreaker", { mScreenSize.x / 2, mScreenSize.y / 2 }, 40);
		Utils::DrawTextCentered("Press SPACE to start", { mScreenSize.x / 2, mScreenSize.y / 3 * 2 }, 20);

		mPaddle.Draw();
		break;

	case GameState::Play:
		mWall.Draw();
		mPaddle.Draw();
		mBall.Draw();
		break;

	case GameState::Loose:
		Utils::DrawTextCentered("You lose!", { mScreenSize.x / 2, mScreenSize.y / 2 }, 40);
		Utils::DrawTextCentered("Press SPACE to restart", { mScreenSize.x / 2, mScreenSize.y / 3 * 2 }, 20);
		mPaddle.Draw();
		break;

	case GameState::Win:
		Utils::DrawTextCentered("You Win!", { mScreenSize.x / 2, mScreenSize.y / 2 }, 40);
		Utils::DrawTextCentered("Press SPACE to continue", { mScreenSize.x / 2, mScreenSize.y / 3 * 2 }, 20);
		mPaddle.Draw();
		break;
	}
}

void Engine::Loose()
{
	cout << "You lose!" << endl;

	mWall = BrickWall(5, 10, mScreenSize);

	mPaddle = Paddle(mPaddlePos, mPaddleSize, mPaddleSpeed, mScreenSize);
	mBall = Ball(mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall);

	mGameState = GameState::Loose;
}

void Engine::Win()
{
	cout << "You win!" << endl;

	if (mWall.GetRows() >= 14) 
	{
		mWall = BrickWall(14, 10, mScreenSize);
	}
	else
	{
		mWall = BrickWall( mWall.GetRows() + 3, 10, mScreenSize);
	}

	mPaddle = Paddle(mPaddlePos, mPaddleSize, mPaddleSpeed, mScreenSize);
	mBall = Ball(mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall);

	mGameState = GameState::Win;
}


