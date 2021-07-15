#include "triangulation.h"

#include <algorithm>
#include <cmath>

QuadEdge* QuadEdge::rev()const{
	return rot->rot;
}

QuadEdge* QuadEdge::lnext()const{
	return rot->rev()->onext->rot;
}

QuadEdge* QuadEdge::oprev()const{
	return rot->onext->rot;
}

Point QuadEdge::dest()const{
	return rev()->origin;
}


Delaunay::Delaunay():
	infPoint(1e18, 1e18)
{}

QuadEdge* Delaunay::makeEdge(Point from, Point to){
	QuadEdge* e1 = new QuadEdge;
	QuadEdge* e2 = new QuadEdge;
	QuadEdge* e3 = new QuadEdge;
	QuadEdge* e4 = new QuadEdge;
	e1->origin = from;
	e2->origin = to;
	e3->origin = e4->origin = infPoint;
	e1->rot = e3;
	e2->rot = e4;
	e3->rot = e2;
	e4->rot = e1;
	e1->onext = e1;
	e2->onext = e2;
	e3->onext = e4;
	e4->onext = e3;
	return e1;
}

void Delaunay::splice(QuadEdge* a, QuadEdge* b) {
	std::swap(a->onext->rot->onext, b->onext->rot->onext);
	std::swap(a->onext, b->onext);
}

void Delaunay::deleteEdge(QuadEdge* e) {
	splice(e, e->oprev());
	splice(e->rev(), e->rev()->oprev());
	delete e->rev()->rot;
	delete e->rev();
	delete e->rot;
	delete e;
}

QuadEdge* Delaunay::connect(QuadEdge* a, QuadEdge* b) {
	QuadEdge* e = makeEdge(a->dest(), b->origin);
	splice(e, a->lnext());
	splice(e->rev(), b);
	return e;
}

bool Delaunay::leftOf(Point p, QuadEdge* e){
	return (p.cross(e->origin, e->dest()) > 0);
}

bool Delaunay::rightOf(Point p, QuadEdge* e){
	return (p.cross(e->origin, e->dest()) < 0);
}

template <class T>
T Delaunay::det3(T a1, T a2, T a3, T b1, T b2, T b3, T c1, T c2, T c3){
	return a1 * (b2 * c3 - c2 * b3) - a2 * (b1 * c3 - c1 * b3) + a3 * (b1 * c2 - c1 * b2);
}

bool Delaunay::inCircle(Point a, Point b, Point c, Point d){
#if defined(__LP64__)||defined(_WIN64)
	__int128 det = -det3<__int128>(b.x, b.y, b.sqrLength(), c.x, c.y, c.sqrLength(), d.x, d.y, d.sqrLength());
	det += det3<__int128>(a.x, a.y, a.sqrLength(), c.x, c.y, c.sqrLength(), d.x, d.y, d.sqrLength());
	det -= det3<__int128>(a.x, a.y, a.sqrLength(), b.x, b.y, b.sqrLength(), d.x, d.y, d.sqrLength());
	det += det3<__int128>(a.x, a.y, a.sqrLength(), b.x, b.y, b.sqrLength(), c.x, c.y, c.sqrLength());
	return det > 0;
#else
	auto ang = [](Point l, Point mid, Point r){
		long long x = mid.dot(l, r);
		long long y = mid.cross(l, r);
		long double res = atan2((long double)x, (long double)y);
		return res;
	};
	long double kek = ang(a, b, c) + ang(c, d, a) - ang(b, c, d) - ang(d, a, b);
	return (kek > 1e-8);
#endif
}

bool Delaunay::valid(QuadEdge* e, QuadEdge* b){
	return rightOf(e->dest(), b);
}

int Delaunay::sgn(const long long &a){
	return a>=0 ? a ? 1 : 0 : -1;	
}

std::pair<QuadEdge*, QuadEdge*> Delaunay::buildTr(int l, int r, std::vector<Point>& p){
	if (r - l + 1 == 2) {
		QuadEdge* res = makeEdge(p[l], p[r]);
		return std::make_pair(res, res->rev());
	}
	if (r - l + 1 == 3) {
		QuadEdge *a = makeEdge(p[l], p[l + 1]), *b = makeEdge(p[l + 1], p[r]);
		splice(a->rev(), b);
		int sg = sgn(p[l].cross(p[l + 1], p[r]));
		if (sg == 0){
			return std::make_pair(a, b->rev());
		}
		QuadEdge* c = connect(b, a);
		if (sg == 1){
			return std::make_pair(a, b->rev());
		}
		return std::make_pair(c->rev(), c);
	}
	int mid = (l + r) / 2;
	QuadEdge *ldo, *ldi, *rdo, *rdi;
	std::tie(ldo, ldi) = buildTr(l, mid, p);
	std::tie(rdi, rdo) = buildTr(mid + 1, r, p);
	while (true) {
		if (leftOf(rdi->origin, ldi)) {
			ldi = ldi->lnext();
			continue;
		}
		if (rightOf(ldi->origin, rdi)) {
			rdi = rdi->rev()->onext;
			continue;
		}
		break;
	}
	QuadEdge* basel = connect(rdi->rev(), ldi);
	if (ldi->origin == ldo->origin){
		ldo = basel->rev();
	}
	if (rdi->origin == rdo->origin){
		rdo = basel;
	}
	while (true) {
		QuadEdge* lcand = basel->rev()->onext;
		if (valid(lcand, basel)) {
			while (inCircle(basel->dest(), basel->origin, lcand->dest(), lcand->onext->dest())) {
				QuadEdge* t = lcand->onext;
				deleteEdge(lcand);
				lcand = t;
			}
		}
		QuadEdge* rcand = basel->oprev();
		if (valid(rcand, basel)) {
			while (inCircle(basel->dest(), basel->origin, rcand->dest(), rcand->oprev()->dest())) {
				QuadEdge* t = rcand->oprev();
				deleteEdge(rcand);
				rcand = t;
			}
		}
		if (!valid(lcand, basel) && !valid(rcand, basel)){
			break;
		}
		if (!valid(lcand, basel) || (valid(rcand, basel) && inCircle(lcand->dest(), lcand->origin, rcand->origin, rcand->dest()))){
			basel = connect(rcand, basel->rev());
		}
		else{
			basel = connect(basel->rev(), lcand->rev());
		}
	}
	return std::make_pair(ldo, rdo);
}

std::vector<std::tuple<Point, Point, Point>> Delaunay::generateMesh(std::vector<Point> p){
	std::sort(p.begin(), p.end(), [](const Point& a, const Point& b){
		return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
	});
	auto res = buildTr(0, (int)p.size()-1, p);
	QuadEdge* e = res.first;
	std::vector<QuadEdge*> edges = {e};
	while (e->onext->dest().cross(e->dest(), e->origin) < 0){
		e = e->onext;
	}
	auto add = [&p, &e, &edges]() {
		QuadEdge* curr = e;
		do {
			curr->used = true;
			p.push_back(curr->origin);
			edges.push_back(curr->rev());
			curr = curr->lnext();
		}
		while (curr != e);
	};
	add();
	p.clear();
	int kek = 0;
	while (kek < (int)edges.size()) {
		if (!(e = edges[kek++])->used){
			add();
		}
	}
	std::vector<std::tuple<Point, Point, Point>> ans;
	for (int i = 0; i < (int)p.size(); i += 3) {
		ans.push_back(std::make_tuple(p[i], p[i + 1], p[i + 2]));
	}
	return ans;
}

//subroutine triangulate
//input : vertex list
//output : triangle list
//   initialize the triangle list
//   determine the supertriangle
//   add supertriangle vertices to the end of the vertex list
//   add the supertriangle to the triangle list
//   for each sample point in the vertex list
//      initialize the edge buffer
//      for each triangle currently in the triangle list
//         calculate the triangle circumcircle center and radius
//         if the point lies in the triangle circumcircle then
//            add the three triangle edges to the edge buffer
//            remove the triangle from the triangle list
//         endif
//      endfor
//      delete all doubly specified edges from the edge buffer
//         this leaves the edges of the enclosing polygon only
//      add to the triangle list all triangles formed between the point 
//         and the edges of the enclosing polygon
//   endfor
//   remove any triangles from the triangle list that use the supertriangle vertices
//   remove the supertriangle vertices from the vertex list
//end
// Suppose an edge e in E , if e meets the following conditions, it is called a Delaunay side:
