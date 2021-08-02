#ifndef WIN_H
#define WIN_H

#include <SFML/Graphics.hpp>
#include <cassert>

namespace win{
	extern sf::RenderWindow window;
	extern sf::View view;
	extern sf::View gui;
	const int width = 1920;
	const int height = 1080;
	const int vwidth = 512;
	const int vheight = 288;
	void init(const char* title);
}

#endif
