#pragma once
#include <string>
#include "Ball.h"
#include "Paddle.h"

using std::string;


class Engine
{
private :
	Ball mBall;
	Paddle mPaddle;

	Vector2 mScreenSize;

public :
	Engine();
	~Engine();

	void Init( Vector2 screenSize );
	void Update();
	void Draw();
};

