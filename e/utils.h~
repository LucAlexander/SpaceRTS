#ifndef UTILS_H
#define UTILS_H

#include <cmath>

namespace utils{
	const float PI = 3.141592;
	const int TPS = 60;
	
	struct v2{
		v2();
		v2(float x, float y);
		float x, y;
		bool compare(v2 other);
	};

	struct Rect{
		Rect();
		Rect(float x, float y, float x2, float y2);
		v2 start, end;	
	};

	float lengthDirX(float length, float dir);
	float lengthDirY(float length, float dir);
	int sign(int val);
	float distancePoint(float x, float y, float xx, float yy);
	int pointDirection(float x, float y, float xx, float yy);
}

#endif
