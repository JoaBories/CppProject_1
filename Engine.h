#pragma once
#include <string>
#include "Ball.h"

using std::string;


class Engine
{
private :
	Ball mBall;

	Vector2 mScreenSize;

public :
	Engine();
	~Engine();

	void Init( Vector2 screenSize );
	void Update();
	void Draw();
};

