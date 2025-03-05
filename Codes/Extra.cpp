#include "Extra.h"

int Extra::randomIntInRange(int min, int max)
{
	// Create a random device and a generator
	static std::random_device rd;
	static std::mt19937 gen(rd());
	// Define the distribution over the desired range [min, max] (inclusive)
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}

int Extra::clampInt(int val, int min, int max)
{
	if (val > max)
		val = max;
	else if (val < min)
		val = min;
	return val;
}

float Extra::lerp(int a, int b, float alpha)
{
	return (a + (b - a) * alpha);
}
