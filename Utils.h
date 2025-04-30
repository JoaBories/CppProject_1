#pragma once
#include "raylib.h"

class Utils
{
private:
	Utils();
	~Utils();

public:
	static float SqrLenght(Vector2 vector);
	static float Lenght(Vector2 vector);
	static Vector2 Normalize(Vector2 vector);
	static Vector2 Distance(Vector2 a, Vector2 b);
	static Vector2 AbsDistance(Vector2 a, Vector2 b);
	static float Min(float a, float b);
	static float Max(float a, float b);
	static float Abs(float value);
	static float FastInvSqrt(float value); // i copied Quake III one
	static float Sqrt(float value);
	static float Clamp(float value, float min, float max);
	static float Lerp(float a, float b, float t);
	static Vector2 Vector2Lerp(Vector2 a, Vector2 b, float t);
};

