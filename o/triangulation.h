#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include<tuple>
#include<vector>
#include<utility>

#include"point.h"

struct QuadEdge{
	Point origin;
	QuadEdge* rot = nullptr;
	QuadEdge* onext = nullptr;
	bool used = false;
	QuadEdge* rev()const;
	QuadEdge* lnext()const;
	QuadEdge* oprev()const;
	Point dest()const;
};

class Delaunay{
public:
	Delaunay();
	std::vector<std::tuple<Point, Point, Point>> generateMesh(std::vector<Point>);
private:
	const Point infPoint;
	std::pair<QuadEdge*, QuadEdge*> buildTr(int l, int r, std::vector<Point>& p);
	bool inCircle(Point a, Point b, Point c, Point d);
	template <class T>
	T det3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3);
	bool rightOf(Point p, QuadEdge* e);
	bool leftOf(Point p, QuadEdge* e);
	QuadEdge* connect(QuadEdge* a, QuadEdge* b);
	void deleteEdge(QuadEdge* e);
	void splice(QuadEdge* a, QuadEdge *b);
	QuadEdge* makeEdge(Point from, Point to);
	int sgn(const long long &a);
	bool valid(QuadEdge* e, QuadEdge* b);
};

#endif
