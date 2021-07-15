#ifndef RANDHANDLER_H
#define RANDHANDLER_H

#include <random>
#include <utility>
#include <chrono>

namespace rnd{
	extern std::random_device randDevice;
	extern std::default_random_engine randEngine;
	extern std::uniform_int_distribution<int> dist;
	long long randInt();
	int iRange(int low, int high);
	bool roll(int upper = 1);
	template<typename t>
	t choose(std::initializer_list<t> list){
		int pos = iRange(0, list.size()-1);
		for (auto i = list.begin();i!=list.end();++i){
			if (pos == 0){
				return *i;
			}
			pos--;
		}
		return *list.begin();
	}
}

#endif
