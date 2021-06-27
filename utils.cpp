#include "utils.h"

float utils::lengthDirX(float length, float dir){
	return length * cos( dir * PI / 180.0 );
}

float utils::lengthDirY(float length, float dir){
	return length * -sin( dir * PI / 180.0 );
}

int utils::sign(int val){
	return val > 0 ? 1 : val == 0 ? 0 : -1;
}


float utils::distancePoint(float x, float y, float xx, float yy){
	x-=xx;
	y-=yy;
	x*=x;
	y*=y;
	return sqrt(x+y);
}
