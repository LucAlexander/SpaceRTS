#include "regionMapping.h"
#include "../e/rnd.h"
#include "triangulation.h"
#include "../e/utils.h"
#include "../e/entityHandler.h"

RegionMapper::RegionMapper():
	mapSize(8),
	partitionSize(64),
	partitionPointCount(2)
{}

RegionMapper::RegionMapper(int size):
	mapSize(size),
	partitionSize(64),
	partitionPointCount(2)
{}

void RegionMapper::setMapSize(int size){
	mapSize = size;
}

void RegionMapper::setPartitionSize(int size){
	partitionSize = size;
}

void RegionMapper::setPartitionPointCount(int count){
	partitionPointCount = count;
}

void RegionMapper::setParams(int ms, int ps, int ppc){
	mapSize = ms;
	partitionSize = ps;
	partitionPointCount = ppc;
}

std::vector<Point> RegionMapper::generatePoints(){
	std::vector<Point> points;
	for (int i = 0;i<mapSize;++i){
		int xoff = i*partitionSize;
		for (int j = 0;j<mapSize;++j){
			int yoff = j*partitionSize;
			int maxPartitionPoints = rnd::iRange(0, partitionPointCount);
			for (int k = 0;k<maxPartitionPoints;++k){
				int xx = rnd::iRange(0, partitionSize)+xoff;
				int yy = rnd::iRange(0, partitionSize)+yoff;
				points.push_back(Point(xx, yy));
			}
		}
	}
	return points;
}

void RegionMapper::generatePlanetPositions(int count, int sepMin, int minSize, int maxSize){
	count /= 2;
	int dist = mapSize/2;
	minSize += sepMin;
	maxSize += sepMin;
	std::vector<Planet*> planets(count*2, nullptr);
	for (int i = 0;i<count;++i){
		int posX = rnd::iRange(0, partitionSize);
		int posY = rnd::iRange(0, partitionSize);
		posX += (rnd::iRange(1, dist-1) * partitionSize);
		posY += (rnd::iRange(1, mapSize-1) * partitionSize);
		int rad = rnd::iRange(minSize, maxSize);
		posX -= rad*2;
		if (planets[i] == nullptr){
			planets[i] = enth::create(posX, posY, Planet());
		}
		planets[i]->setX(posX);
		planets[i]->setY(posY);
		planets[i]->setRadius(rad);
		bool collides = false;
		for (int k = 0;!collides && k<i;++k){
			if (planets[k]->intersects(posX, posY, rad)){
				i--;
				collides = true;
			}
		}
	}
	for(int i = 0;i<count;++i){
		planets[i]->setRadius(planets[i]->getRadius()-sepMin);
		utils::v2 pos(planets[i]->getX(), planets[i]->getY());
		float rad = planets[i]->getRadius();
		planets[count+i] = enth::create((mapSize*partitionSize)-pos.x-(rad*2), (mapSize*partitionSize)-pos.y-(rad*2), Planet());
		planets[count+i]->setRadius(rad);
	}
}

std::vector<Point> RegionMapper::generateStarPositions(int spirals, int density){
	std::vector<Point> stars;
	int axis, cx, cy, len, dir, lenChange, dirChange, border;
	axis = mapSize*partitionSize;
	border = 64;
	dirChange = 15;
	for (int i = 0;i<spirals;++i){
		cx = axis/2;
		cy = axis/2;
		len = 8;
		dir = 0 + (i*(360/spirals));
		lenChange = len;
		while(cx > border && cy > border && cx < axis-border && cy < axis-border){
			cx += utils::lengthDirX(len, dir);
			cy += utils::lengthDirY(len, dir);
			len += lenChange;
			dir += dirChange%360;
			stars.push_back(Point(cx, cy));
			int posx, posy;
			posx = 0;
			posy = 0;
			for (int i = 0;i<density;++i){
				posx = cx+utils::lengthDirX(rnd::iRange(1, density*2), rnd::iRange(0, 359));
				posy = cy+utils::lengthDirY(rnd::iRange(1, density*2), rnd::iRange(0, 359));
				if (posx > border/2 && posx < axis-(border/2) && posy > border/2 && posy < axis-(border/2)){
					stars.push_back(Point(posx, posy));
				}
			}
		}
	}
	return stars;
}

std::vector<Partition> RegionMapper::generateTriangles(std::vector<Point> points){
	Delaunay tri;
	auto triangles = tri.generateMesh(points);
	std::vector<Partition> regions;
	for (int i = 0;i<triangles.size();++i){
		std::tuple<Point, Point, Point> u = triangles[i];
		Partition t = Partition(std::get<0>(u), std::get<1>(u), std::get<2>(u));
		t.line0[0] = sf::Vertex(sf::Vector2f(t.a.x, t.a.y), sf::Color(127, 127, 255, 127));
		t.line0[1] = sf::Vertex(sf::Vector2f(t.b.x, t.b.y), sf::Color(127, 127, 255, 127));
		t.line1[0] = sf::Vertex(sf::Vector2f(t.b.x, t.b.y), sf::Color(127, 127, 255, 127));
		t.line1[1] = sf::Vertex(sf::Vector2f(t.c.x, t.c.y), sf::Color(127, 127, 255, 127));
		t.line2[0] = sf::Vertex(sf::Vector2f(t.a.x, t.a.y), sf::Color(127, 127, 255, 127));
		t.line2[1] = sf::Vertex(sf::Vector2f(t.c.x, t.c.y), sf::Color(127, 127, 255, 127));
		regions.push_back(t);
	}
	return regions;
}
