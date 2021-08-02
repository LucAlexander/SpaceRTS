#include "win.h"
#include "utils.h"

sf::RenderWindow win::window(sf::VideoMode(win::width, win::height), "", sf::Style::Titlebar | sf::Style::Close);
sf::View win::view(sf::Vector2f(win::vwidth/2, win::vheight/2), sf::Vector2f(win::vwidth, win::vheight));
sf::View win::gui(sf::Vector2f(win::vwidth/2, win::vheight/2), sf::Vector2f(win::vwidth, win::vheight));

void win::init(const char* title){
	window.setTitle(title);
	window.setView(view);
}
