#include "win.h"
#include "utils.h"

sf::RenderWindow win::window(sf::VideoMode(win::width, win::height), "Space RTS", sf::Style::Titlebar | sf::Style::Close);
sf::View win::view(sf::Vector2f(win::vwidth/2, win::vheight/2), sf::Vector2f(win::vwidth, win::vheight));

void win::init(){
	window.setView(view);
}
