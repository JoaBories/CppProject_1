#pragma once
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "BrickWall.h"

using std::string;


class Engine
{
private :
	Ball mBall;
	Paddle mPaddle;

	BrickWall mWall;

	Vector2 mScreenSize;

public :
	Engine();
	~Engine();

	void Init( Vector2 screenSize );
	void Update();
	void Draw() const;
};

