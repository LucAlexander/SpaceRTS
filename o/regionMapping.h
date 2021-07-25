#ifndef REGIONMAPPING_H
#define REGIONMAPPING_H

#include <utility>
#include <vector>

#include "point.h"
#include "planet.h"
#include "partition.h"

class RegionMapper{
public:
	RegionMapper();
	RegionMapper(int size);
	void setMapSize(int size);
	void setPartitionSize(int size);
	void setPartitionPointCount(int count);
	void setParams(int ms, int ps, int ppc);
	std::vector<Point> generatePoints();
	std::vector<Point> generateStarPositions(int spirals, int density);
	std::vector<Planet*> generatePlanetPositions(int count, int sepMin, int minSize, int maxSize);
	std::vector<Partition> generateTriangles(std::vector<Point>);
private:
	int mapSize;
	int partitionSize;
	int partitionPointCount;
};

#endif
