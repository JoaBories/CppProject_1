#pragma once
#include "raylib.h"
#include "Utils.h"


class Bonus
{
private :
	Vector2 mPosition;
	float mRadius;
	float mSpeed;

public :
	Bonus();
	~Bonus();
	Bonus(Vector2 startPos, float radius, float speed);

	void Update();
	void Draw() const;

	Vector2 GetPosition() const;

	bool ResolvePaddleAABB(Vector2 position, Vector2 size) const;
};

