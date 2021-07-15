#include"point.h"

Point::Point():
	x(0),
	y(0)
{}

Point::Point(long long a, long long b):
	x(a),
	y(b)
{}

Point Point::operator - (const Point& p)const{
	return Point(x-p.x, y-p.y);
}

bool Point::operator == (const Point& p)const{
	return (x==p.x)&&(y==p.y);
}

long long Point::cross(const Point& p)const{
	return (x*p.y-y*p.x);
}

long long Point::cross(const Point& a, const Point& b)const{
	return (a-*this).cross(b-*this);
}

long long Point::dot(const Point& p)const{
	return x*p.x+y*p.y;
}

long long Point::dot(const Point& a, const Point& b)const{
	return (a-*this).dot(b-*this);
}

long long Point::sqrLength()const{
	return this->dot(*this);
}


