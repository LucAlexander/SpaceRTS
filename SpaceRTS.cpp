#include "game.h"

#include "rnd.h"
#include "point.h"
#include "triangulation.h"
#include "nationGenerator.h"
#include "regionMapping.h"
#include "unit.h"
#include "unitTarget.h"
#include "win.h"
#include "entityHandler.h"

int main(int argc, char** argv){
	Game SpaceRTS = Game("SpaceRTS");
	SpaceRTS.setInitCode([](){
		// MAPPING INSTANTIATION AND MAKING TRIANGLE MESH
		RegionMapper mapper = RegionMapper(16);
		std::vector<Partition> regions = mapper.generateTriangles(mapper.generatePoints());
		
		/* CIV NAME GENERATION
		sf::Font font;
		if (!font.loadFromFile("FSEX300.ttf")){
			return -1;
		}
		NationGenerator gen;
		std::string name = "";
		for (int i = 0;i<6;++i){
			name += gen.generate("indonesian") + "\n";
		}
		sf::Text message(name, font);
		*/

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
		std::vector<Planet> planets = mapper.generatePlanetPositions(64, 8, 5, 25);
		
		// UNIT BOID TESTING
		for (int i = 0;i<1;++i){
			Unit* instance = enth::create(rnd::iRange(0, 32)*6, rnd::iRange(0, 32)*6, Unit());
			int angle = rnd::iRange(0, 24)*15;
			instance->setDirection(angle);
		}
		UnitTarget* uTarget = enth::create(512, 512, UnitTarget());
	});
	SpaceRTS.loop();
	SpaceRTS.close();
	return 0;
}
