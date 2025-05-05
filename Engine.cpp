#include "Engine.h"

#include <chrono>
using namespace std::chrono;

using std::to_string;

Engine::Engine() :
	mPaddle{ Paddle() },
	mBalls{ new Ball() },
	mBonuses{ new Bonus() },
	mScreenSize{ 0,0 },
	mPaddlePos{ 0,0 },
	mPaddleSize{ 0,0 },
	mPaddleSpeed{ 0 },
	mBallPos{ 0,0 },
	mBallSpeed{ 0 },
	mBallRadius{ 0 },
	mYLoosePosition{ 0 },
	mWall{ BrickWall() },
	mGameState{ Start },
	mScore{ 0 }
{
}

Engine::~Engine()
{
	for (Ball* b : mBalls) {
		delete b;
	}
	mBalls.clear();
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

	mBonuses.clear();

	mPaddle = Paddle( mPaddlePos, mPaddleSize, mPaddleSpeed, mScreenSize);
	mBalls.clear();
	mBalls.push_back(new Ball(mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall, &mScore));
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

		for (size_t i = 0; i < mBalls.size(); i++)
		{
			mBalls[i]->Update();

			if (mBalls[i]->GetTryBonus().x != 0 || mBalls[i]->GetTryBonus().y != 0)
			{
				TrySpawnBonus(mBalls[i]->GetTryBonus());
				mBalls[i]->ResetTryBonus();
			}

			if(mBalls[i]->GetPosition().y >= mYLoosePosition)
			{
				delete mBalls[i];
				mBalls.erase(mBalls.begin() + i);
			}
		}

		for (size_t i = 0; i < mBonuses.size(); i++)
		{
			mBonuses[i]->Update();

			if (mBonuses[i]->GetPosition().y >= mScreenSize.y / 20 * 17)
			{
				if (mBonuses[i]->ResolvePaddleAABB(mPaddle.GetPosition(), mPaddle.GetSize()))
				{
					delete mBonuses[i];
					mBonuses.erase(mBonuses.begin() + i);

					mBalls.push_back(new Ball(mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall, &mScore));
					break;
				}
			}

			if (mBonuses[i]->GetPosition().y >= mYLoosePosition)
			{
				delete mBonuses[i];
				mBonuses.erase(mBonuses.begin() + i);
				break;
			}
		}
		
		if (mWall.GetNumberOfBricks() == 0)
		{
			Win();
		}

		if (mBalls.size() == 0)
		{
			Loose();
		}

		break;

	case GameState::Loose:
		if (IsKeyPressed(KEY_SPACE))
		{
			mScore = 0;

			mWall = BrickWall(5, 10, mScreenSize);

			mPaddle = Paddle(mPaddlePos, mPaddleSize, mPaddleSpeed, mScreenSize);
			mBalls.clear();
			mBalls.push_back(new Ball(mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall, &mScore));

			mGameState = GameState::Play;
		}

		mPaddle.Update();
		break;

	case GameState::Win:
		if (IsKeyPressed(KEY_SPACE))
		{
			if (mWall.GetRows() >= 14)
			{
				mWall = BrickWall(14, 10, mScreenSize);
			}
			else
			{
				mWall = BrickWall(mWall.GetRows() + 3, 10, mScreenSize);
			}

			mPaddle = Paddle(mPaddlePos, mPaddleSize, mPaddleSpeed, mScreenSize);
			mBalls.clear();
			mBalls.push_back(new Ball(mBallPos, mBallSpeed, mBallRadius, mScreenSize, &mPaddle, &mWall, &mScore));

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
		Utils::DrawTextCentered(to_string(mScore), { mPaddle.GetPosition().x, mScreenSize.y / 4 * 3}, 40);

		mWall.Draw();
		mPaddle.Draw();

		for (Ball* ball : mBalls)
		{
			ball->Draw();
		}

		for (Bonus* bonus : mBonuses)
		{
			bonus->Draw();
		}

		break;

	case GameState::Loose:
		Utils::DrawTextCentered("Your Score : " + to_string(mScore), {mScreenSize.x / 2, mScreenSize.y / 3}, 40);
		Utils::DrawTextCentered("You lose!", { mScreenSize.x / 2, mScreenSize.y / 2 }, 40);
		Utils::DrawTextCentered("Press SPACE to restart", { mScreenSize.x / 2, mScreenSize.y / 3 * 2 }, 20);
		mPaddle.Draw();
		break;

	case GameState::Win:
		Utils::DrawTextCentered(to_string(mScore), { mScreenSize.x / 2, mScreenSize.y / 3 }, 40);
		Utils::DrawTextCentered("You Win!", { mScreenSize.x / 2, mScreenSize.y / 2 }, 40);
		Utils::DrawTextCentered("Press SPACE to continue", { mScreenSize.x / 2, mScreenSize.y / 3 * 2 }, 20);
		mPaddle.Draw();
		break;
	}
}

void Engine::Loose()
{
	cout << "You lose!" << endl;
	mGameState = GameState::Loose;
}

void Engine::Win()
{
	cout << "You win!" << endl;
	mGameState = GameState::Win;
}

void Engine::TrySpawnBonus(Vector2 pos)
{
	if (Utils::RandInt(0,100) >= 50)
	{
		mBonuses.push_back(new Bonus(pos, 10, 100));
	}
}


