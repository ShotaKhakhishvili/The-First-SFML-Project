#pragma once
#include <random>

#define M_PI 3.14159265358979323846f

class Extra
{
public:
	static int randomIntInRange(int min, int max);
	static int clampInt(int val, int min, int max);
	static float lerp(int a, int b, float alpha);
};

