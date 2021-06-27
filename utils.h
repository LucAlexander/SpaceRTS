#ifndef UTILS_H
#define UTILS_H

#include <cmath>

namespace utils{
	const float PI = 3.141592;
	const int TPS = 60;
	float lengthDirX(float length, float dir);
	float lengthDirY(float length, float dir);
	int sign(int val);
	float distancePoint(float x, float y, float xx, float yy);
}

#endif
