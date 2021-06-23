#ifndef PARTITION_H
#define PARTITION_H

#include <sfml/Graphics.hpp>

#include "point.h"

struct Partition{
	Partition();
	Partition(Point aa, Point bb, Point cc);
	Point a;
	Point b;
	Point c;
	sf::Vertex line0[2];
	sf::Vertex line1[2];
	sf::Vertex line2[2];
	float area();
	float triangleArea(Point p1, Point p2, Point p3);
	bool contains(Point p);
};

#endif
