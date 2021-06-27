#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>

#include <SFML/Graphics.hpp>
#include <cassert>

#include"rnd.h"
#include"point.h"
#include"triangulation.h"
#include"generator.h"
#include"regionMapping.h"
#include"unit.h"
#include"entityHandler.h"

Generator::Generator(){
	readIn("syllables.txt", syllables);
	readIn("adjectives.txt", adjectives);
	readIn("surroundings.txt", surroundings);
}

void Generator::readIn(std::string file, std::map<std::string, std::vector<std::string>>& structure){
	std::string dir = "./lists/"+file;
	std::ifstream infile(dir);
	std::string line;
	std::string division = "";
	while(infile){
		std::getline(infile, line);
		char c = line[0];
		switch(c){
			case ':':
				division = line.substr(1, line.length()-1);
			break;
			default:
				if (division!=""&&line!=""){
					structure[division].push_back(line);
				}
			break;
		}
	}
	infile.close();
}

std::string Generator::getPrefix(){
	/* PREFIX SYNTAX
	 * prefix
	 * of
	 * trailing space
	*/
	int len = surroundings["prefixes"].size()-1;
	return fixCase(surroundings["prefixes"][rnd::iRange(0, len)]) + " of ";
}

std::string Generator::getSuffix(){
	/* SUFFIX SYNTAX
	 * suffix
	*/
	int len = surroundings["suffixes"].size()-1;
	return fixCase(surroundings["suffixes"][rnd::iRange(0, len)]);
}

std::string Generator::getAdjective(){
	/* ADJECTIVE SYNTAX
	 * the
	 * either adjective or color(1 in 4)
	 * trailing space
	*/
	std::string type = rnd::iRange(0, 3) > 0?"standard":"color";
	int len = adjectives[type].size()-1;
	return "the " + fixCase(adjectives[type][rnd::iRange(0, len)]) + " ";
}

std::string Generator::getName(std::string langFamily){
	/* NAME SYNTAX
	 * 2 <= syllables <= 4
	 * all syllables are from a given language family
	 * trailing space
	*/
	std::string name = "";
	int sylCount = rnd::iRange(2, 4);
	int len = syllables[langFamily].size()-1;
	for (int i = 0;i<sylCount;++i){
		name += syllables[langFamily][rnd::iRange(0, len)];
	}
	return fixCase(name) + " ";
}

std::string Generator::genFactionName(std::string langFamily){
	/* FACTION NAME SYNTAX
	 * adjective is a 1 in 3 chance
	 * name[i] : nameCount=c where {c : Z | 0 < c <= 2 }, weighted at 1
	 * if an adjective is present, c may be 0
	*/ 
	std::string adjective = rnd::iRange(0, 2) ? "" : getAdjective();
	std::string name = adjective;
	int lowBound = (adjective=="") ? 1 : rnd::iRange(0, 1);
	int nameCount = rnd::iRange(lowBound, 2);
	nameCount = rnd::iRange(nameCount, 1);
	for (int i = 0;i<nameCount;++i){
		name += getName(langFamily);
	}
	return name;
}

std::string Generator::generate(std::string langFamily){
	/* STRUCTURE SYNTAX
	 * none   0
	 * prefix 1
	 * suffix 2
	 * both   3
	*/
	int structure = rnd::iRange(0, 3);
	std::string prefix = (structure&1)?getPrefix():"";
	std::string suffix = (structure>1)?getSuffix():"";
	std::string name = genFactionName(langFamily);
	name = prefix + name + suffix;
	for (int i = name.length()-1;i>=0;--i){
		if (name[i]!=' '){
			name = name.substr(0, i+1);
			break;
		}
	}
	if (countWords(name) >= 3){
		name += "("+generateAcronym(name)+")";
	}
	return name;
}

std::string Generator::fixCase(std::string name){
	for (int i = 0;i<name.length();++i){
		if (i==0 || name[i-1]==' '){
			if (name[i]>=97){
				name[i] -= 32;
			}
		}
	}
	return name;
}

std::string Generator::generateAcronym(std::string name){
	std::string acr = "";
	for (int i = 0;i<name.length();++i){
		if (name[i]<=90&&name[i]!=' '){
			acr += name[i];
		}
	}
	return acr;
}

int Generator::countWords(std::string name){
	int count = 0;
	for (int i = 0;i<name.length();++i){
		if (name[i]==' '){
			count++;
		}
	}
	return count;
}

// FOREWARD DECLARATIONS OF LOOP FUNCTIONS
void update();
void draw();


int main(int argc, char** argv){
	// MAPPING INSTANTIATION AND MAKING TRIANGLE MESH
	RegionMapper mapper = RegionMapper(16);
	std::vector<Partition> regions = mapper.generateTriangles(mapper.generatePoints());
	
	// WINDOW AND CAMERA INSTANTIATIOIN
	sf::RenderWindow sfmlWin(sf::VideoMode(1920, 1080), "Nation Generator", sf::Style::Titlebar | sf::Style::Close);
	sf::View cam(sf::Vector2f(800, 300), sf::Vector2f(512, 288));
	sfmlWin.setView(cam);

	/* CIV NAME GENERATION
	sf::Font font;
	if (!font.loadFromFile("FSEX300.ttf")){
		return -1;
	}
	Generator gen;
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
