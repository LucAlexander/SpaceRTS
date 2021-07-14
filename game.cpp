#include "game.h"
#include "win.h"
#include "entityHandler.h"

Game::Game():
	Game("demo")
{}

Game::Game(const char* title):
	clock(),
	elapsedTime(),
	frameTime(1000/utils::TPS),
	initCode([](){})
{
	win::init(title);
}

void Game::setInitCode(std::function<void()> code){
	initCode = code;
}

void Game::update(){
	sf::View gCam = win::window.getView();
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
	win::window.setView(gCam);
	for (auto mit : enth::entityList){
		for (auto vit : mit.second){
			vit->update();
		}
	}
}

void Game::draw(){
	std::vector<Entity*> order;
	for (auto mit : enth::entityList){
		for (auto vit : mit.second){
			int dep = vit->getDepth();
			int index = 0;
			for (auto dvit : order){
				if (dvit->getDepth()>dep){
					break;
				}
				index++;
			}
			order.insert(order.begin()+index, vit);
		}
	}
	for (auto vit : order){
		float hbx, hby, hbw, hbh;
		hbx = vit->getGlobalHitbox().start.x;
		hby = vit->getGlobalHitbox().start.y;
		hbw = vit->getGlobalHitbox().end.x-hbx;
		hbh = vit->getGlobalHitbox().end.y-hby;
		sf::RectangleShape hb(sf::Vector2f(hbw, hbh));
		hb.setPosition(sf::Vector2f(hbx, hby));
		hb.setFillColor(sf::Color::Red);
		win::window.draw(hb);
		vit->draw();
	}
}

void Game::loop(){
	// RUN INITIALIZATION CODE
	initCode();
	// SET UP LOOP PARAMS
	int frameTime = 1000/utils::TPS;
	clock.restart();
	// MAIN LOOP
	while(win::window.isOpen()){
		sf::Event e;
		while(win::window.pollEvent(e)){
			switch(e.type){
				case sf::Event::Closed:
					win::window.close();
				break;
			}
		}
		elapsedTime += clock.restart().asMilliseconds();
		// UPDATE CODE
		while(elapsedTime>frameTime){
			elapsedTime-=frameTime;
			update();
		}
		// DRAW CODE
		win::window.clear();
		draw();
		win::window.display();
	}
}

void Game::close(){
	// CLEAR POINTER MEMORY
	txtab::close();
	enth::close();
}

