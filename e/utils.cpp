#include "utils.h"

utils::v2::v2():
	v2(0, 0)
{}

utils::v2::v2(float xx, float yy):
	x(xx),
	y(yy)
{}

bool utils::v2::compare(v2 other){
	return x==other.x&&y==other.y;
}

utils::Rect::Rect():
	Rect(0, 0, 0, 0)
{}

utils::Rect::Rect(float x, float y, float xx, float yy):
	start(x, y),
	end(xx, yy)
{}

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

int utils::pointDirection(float x, float y, float xx, float yy){
	float val = atan2(yy-y, xx-x) * (180/PI);
	val = (val<0)?-val:360-val;
	return (int)(val) % 360;
}

bool utils::pointInRect(v2 p, Rect r){
	return (p.x >= r.start.x && p.x <= r.end.x) && 
		(p.y >= r.start.y && p.y <= r.end.y);

}
