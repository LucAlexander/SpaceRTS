#ifndef NATIONGENERATOR_H
#define NATIONGENERATOR_H

#include "../e/entity.h"

#include <vector>
#include <map>

class NationGenerator : public Entity{
public:
	NationGenerator();
	void init();
	std::string generate(std::string langFamily);
private:
	std::map<std::string, std::vector<std::string>> syllables;
	std::map<std::string, std::vector<std::string>> adjectives;
	std::map<std::string, std::vector<std::string>> surroundings;
	void readIn(std::string, std::map<std::string, std::vector<std::string>>& structure);
	std::string genFactionName(std::string langFamily);
	std::string getPrefix();
	std::string getSuffix();
	std::string getAdjective();
	std::string getName(std::string langFamily);
	std::string generateAcronym(std::string name);
	std::string fixCase(std::string);
	int countWords(std::string);
};

#endif
