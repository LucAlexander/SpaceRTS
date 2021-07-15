#ifndef TEXTURE_TABLE_H
#define TEXTURE_TABLE_H

#include <SFML/Graphics.hpp>
#include <map>

namespace txtab{
	extern std::map<const char*, sf::Texture*> index;
	sf::Texture* load(const char* dir);
	void close();
}

#endif
