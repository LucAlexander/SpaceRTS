#include"partition.h"

#include <cmath>

Partition::Partition():
	a(),
	b(),
	c()
{}

Partition::Partition(Point aa, Point bb, Point cc):
	a(aa),
	b(bb),
	c(cc)
{}

float Partition::triangleArea(Point p1, Point p2, Point p3){
	return abs((p1.x*(p2.y-p3.y) + p2.x*(p3.y-p1.y)+ p3.x*(p1.y-p2.y))/2.0);
}

float Partition::area(){
	return triangleArea(a, b, c);
}

bool Partition::contains(Point p){
	float area = triangleArea (a, b, c);
	float area1 = triangleArea (p, b, c);
	float area2 = triangleArea (a, p, c);
	float area3 = triangleArea (a, b, p);
	return (area == area1 + area2 + area3);
}
