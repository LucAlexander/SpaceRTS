#include "textureTable.h"

std::map<const char*, sf::Texture*> txtab::index;

sf::Texture* txtab::load(const char* dir){
	if (index.count(dir)>0){
		return index[dir];
	}
	sf::Texture* tex = new sf::Texture();
	std::string relativeDir(dir);
	relativeDir = "./s/" + relativeDir;
	tex->loadFromFile(relativeDir);
	tex->setSmooth(false);
	index[dir] = tex;
}

void txtab::close(){
	for (auto i : index){
		delete i.second;
	}
}
