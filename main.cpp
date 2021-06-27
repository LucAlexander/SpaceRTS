#include <SFML/Graphics.hpp>
#include <cassert>

#include "rnd.h"
#include "point.h"
#include "triangulation.h"
#include "nationGenerator.h"
#include "regionMapping.h"
#include "unit.h"
#include "entityHandler.h"

#include <iostream>

// FOREWARD DECLARATIONS OF LOOP FUNCTIONS
void update();
void draw();


int main(int argc, char** argv){
	// MAPPING INSTANTIATION AND MAKING TRIANGLE MESH
	RegionMapper mapper = RegionMapper(16);
	std::vector<Partition> regions = mapper.generateTriangles(mapper.generatePoints());
	
	// WINDOW AND CAMERA INSTANTIATIOIN
	sf::RenderWindow sfmlWin(sf::VideoMode(1920, 1080), "Space RTS demo", sf::Style::Titlebar | sf::Style::Close);
	sf::View cam(sf::Vector2f(800, 300), sf::Vector2f(512, 288));
	sfmlWin.setView(cam);

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
	Unit* ship = enth::instanceCreate(Unit());

	sf::Clock clock;
	sf::Int32 elapsedTime;
	int frameTime = 1000/utils::TPS;
	while(sfmlWin.isOpen()){
		sf::Event e;
		while(sfmlWin.pollEvent(e)){
			switch(e.type){
				case sf::Event::Closed:
					sfmlWin.close();
				break;
			}
		}
		elapsedTime += clock.restart().asMilliseconds();
		while(elapsedTime>frameTime){
			elapsedTime-=frameTime;
			//UPDATE CODE
			sf::View gCam = sfmlWin.getView();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
				gCam.zoom(0.99);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
				gCam.zoom(1.01);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				gCam.move(0, -5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
				gCam.move(-5, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				gCam.move(0, 5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				gCam.move(5, 0);
			}
			sfmlWin.setView(gCam);
			update();
		}
		// DRAW CODE
		sfmlWin.clear();
		for (int i = 0;i<regions.size();++i){
			sfmlWin.draw(regions[i].line0, 2, sf::Lines);
			sfmlWin.draw(regions[i].line1, 2, sf::Lines);
			sfmlWin.draw(regions[i].line2, 2, sf::Lines);
		}
		//for (int i=0;i<stars.size();++i){
		//	sfmlWin.draw(&stars[i], 1, sf::Points);
		//}
		/*for(int i =0;i<planets.size();++i){
			sfmlWin.draw(planets[i].getSprite());
		}*/
		//sfmlWin.draw(message);
		sfmlWin.draw(ship->getSprite()); // TODO replace with draw();
		sfmlWin.display();
	}
	// CLEAR POINTER MEMORY
	txtab::close();
	enth::close();
	return 0;
}

void update(){
	for (auto mit : enth::entityList){
		for (auto vit : mit.second){
			vit->update();
		}
	}
}

void draw(){
	for (auto mit : enth::entityList){
		for (auto vit : mit.second){
			vit->draw();
		}
	}
}
