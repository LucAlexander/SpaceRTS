#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string>

#include"../e/rnd.h"
#include"nationGenerator.h"

NationGenerator::NationGenerator(){
	readIn("syllables.txt", syllables);
	readIn("adjectives.txt", adjectives);
	readIn("surroundings.txt", surroundings);
}

void NationGenerator::readIn(std::string file, std::map<std::string, std::vector<std::string>>& structure){
	std::string dir = "./f/"+file;
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

std::string NationGenerator::getPrefix(){
	/* PREFIX SYNTAX
	 * prefix
	 * of
	 * trailing space
	*/
	int len = surroundings["prefixes"].size()-1;
	return fixCase(surroundings["prefixes"][rnd::iRange(0, len)]) + " of ";
}

std::string NationGenerator::getSuffix(){
	/* SUFFIX SYNTAX
	 * suffix
	*/
	int len = surroundings["suffixes"].size()-1;
	return fixCase(surroundings["suffixes"][rnd::iRange(0, len)]);
}

std::string NationGenerator::getAdjective(){
	/* ADJECTIVE SYNTAX
	 * the
	 * either adjective or color(1 in 4)
	 * trailing space
	*/
	std::string type = rnd::iRange(0, 3) > 0?"standard":"color";
	int len = adjectives[type].size()-1;
	return "the " + fixCase(adjectives[type][rnd::iRange(0, len)]) + " ";
}

std::string NationGenerator::getName(std::string langFamily){
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

std::string NationGenerator::genFactionName(std::string langFamily){
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

std::string NationGenerator::generate(std::string langFamily){
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

std::string NationGenerator::fixCase(std::string name){
	for (int i = 0;i<name.length();++i){
		if (i==0 || name[i-1]==' '){
			if (name[i]>=97){
				name[i] -= 32;
			}
		}
	}
	return name;
}

std::string NationGenerator::generateAcronym(std::string name){
	std::string acr = "";
	for (int i = 0;i<name.length();++i){
		if (name[i]<=90&&name[i]!=' '){
			acr += name[i];
		}
	}
	return acr;
}

int NationGenerator::countWords(std::string name){
	int count = 0;
	for (int i = 0;i<name.length();++i){
		if (name[i]==' '){
			count++;
		}
	}
	return count;
}

