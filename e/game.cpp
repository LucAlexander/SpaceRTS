#include "game.h"
#include "win.h"
#include "entityHandler.h"
#include "input.h"
#include "debug.h"
#include "settings.h"

Game::Game():
	Game("demo")
{}

Game::Game(const char* title):
	clock(),
	elapsedTime(),
	frameTime(1000/settings::TPS),
	initCode([](){})
{
	win::init(title);
}

void Game::setInitCode(std::function<void()> code){
	initCode = code;
}

void Game::update(){
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
		vit->draw();
		if (dbug::showHb){
			float hbx, hby, hbw, hbh;
			hbx = vit->getGlobalHitbox().start.x;
			hby = vit->getGlobalHitbox().start.y;
			hbw = vit->getGlobalHitbox().end.x-hbx;
			hbh = vit->getGlobalHitbox().end.y-hby;
			sf::RectangleShape hb(sf::Vector2f(hbw, hbh));
			hb.setPosition(sf::Vector2f(hbx, hby));
			hb.setOutlineThickness(1);
			hb.setOutlineColor(sf::Color::White);
			hb.setFillColor(sf::Color(0, 0, 0, 0));
			win::window.draw(hb);
		}
	}
	sf::View gameView = win::window.getView();
	win::window.setView(win::gui);
	for (auto vit : order){
		vit->drawGui();
	}
	win::window.setView(gameView);
}

void Game::loop(){
	// RUN INITIALIZATION CODE
	initCode();
	// SET UP LOOP PARAMS
	clock.restart();
	// MAIN LOOP
	while(win::window.isOpen()){
		sf::Event e;
		while(win::window.pollEvent(e)){
			switch(e.type){
				case sf::Event::Closed:
					win::window.close();
				break;
				case sf::Event::KeyPressed:
					inp::keyDownEvent(e.key.code);
				break;
				case sf::Event::KeyReleased:
					inp::keyUpEvent(e.key.code);
				break;
				case sf::Event::MouseButtonPressed:
					inp::mouseDownEvent(e.mouseButton.button);
				break;
				case sf::Event::MouseButtonReleased:
					inp::mouseUpEvent(e.mouseButton.button);
				break;
				case sf::Event::MouseWheelMoved:
					inp::mouseScrollEvent(e.mouseWheel.delta);
				break;
			}
		}
		elapsedTime += clock.restart().asMilliseconds();
		// UPDATE CODE
		while(elapsedTime>frameTime){
			elapsedTime-=frameTime;
			update();
			inp::newFrame();
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

