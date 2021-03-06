#include "e/game.h"
#include "e/rnd.h"
#include "e/win.h"
#include "e/entityHandler.h"

#include "o/point.h"
#include "o/triangulation.h"
#include "o/nationGenerator.h"
#include "o/regionMapping.h"
#include "o/unit.h"
#include "o/player.h"
#include "o/bot.h"

#include <iostream>

int main(int argc, char** argv){
	Game SpaceRTS = Game("SpaceRTS");
	SpaceRTS.setInitCode([](){
		// CIV NAME GENERATION
		enth::create(0, 0, NationGenerator());	

		// MAPPING INSTANTIATION AND MAKING TRIANGLE MESH
		RegionMapper mapper = RegionMapper(16);
		std::vector<Partition> regions = mapper.generateTriangles(mapper.generatePoints());
		
		// GALAXY POINT GENERATION
		int density, spirals;
		density = rnd::choose<int>({64, 80, 96, 112, 128});
		spirals = rnd::iRange(1, 10);
		std::vector<Point> starsPos = mapper.generateStarPositions(10, 64);
		//std::cout << "density: " << density << "\nspirals: " << spirals << "\n";
		std::vector<sf::Vertex> stars;
		for (int i = 0;i<starsPos.size();++i){
			float xx, yy;
			xx = starsPos[i].x;
			xx += 0.5;
			yy = starsPos[i].y;
			yy += 0.5;
			stars.push_back(sf::Vertex(sf::Vector2f(xx, yy), sf::Color(255, 255, 255)));
		}
		
		// PLANET POINT INSTANTIATION
		mapper.generatePlanetPositions(64, 8, 5, 25);
	
		enth::create(0, 0, Player());
		enth::create(0, 0, Bot());

		// UNIT BOID TESTING
		/*for (int i = 0;i<10;++i){
			Unit* instance = enth::create(rnd::iRange(0, 32)*6, rnd::iRange(0, 32)*6, Unit());
		}
		UnitTarget* uTarget = enth::create(512, 512, UnitTarget());
		*/
	});
	SpaceRTS.loop();
	SpaceRTS.close();
	return 0;
}
