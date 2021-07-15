#ifndef POINT_H
#define POINT_H

struct Point{
	long long x, y;
	Point();
	Point(long long x, long long y);
	Point operator - (const Point& p)const;
	bool operator == (const Point& p)const;
	long long cross(const Point& p)const;
	long long cross(const Point& a, const Point& b)const;
	long long dot(const Point& p)const;
	long long dot(const Point& a, const Point& b)const;
	long long sqrLength()const;
};

#endif
