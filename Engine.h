#pragma once
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "BrickWall.h"

using std::string;

enum GameState
{
	Start,
	Play,
	Loose,
	Win,
};

class Engine
{
private :
	Ball mBall;
	Paddle mPaddle;

	BrickWall mWall;

	Vector2 mScreenSize;

	//init parameters
	Vector2 mPaddlePos;
	Vector2 mPaddleSize;
	float mPaddleSpeed;

	Vector2 mBallPos;
	float mBallSpeed;
	float mBallRadius;

	float mYLoosePosition;

	GameState mGameState;

public :
	Engine();
	~Engine();

	void Init( Vector2 screenSize );
	void Update();
	void Draw() const;
	void Loose();
	void Win();
};

