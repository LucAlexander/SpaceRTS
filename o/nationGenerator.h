#ifndef NATIONGENERATOR_H
#define NATIONGENERATOR_H

#include <vector>
#include <map>

struct NationGenerator{
	NationGenerator();
	void readIn(std::string, std::map<std::string, std::vector<std::string>>& structure);
	std::map<std::string, std::vector<std::string>> syllables;
	std::map<std::string, std::vector<std::string>> adjectives;
	std::map<std::string, std::vector<std::string>> surroundings;
	std::string generate(std::string langFamily);
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
