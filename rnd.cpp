#include "rnd.h"

std::random_device rnd::randDevice;
std::default_random_engine rnd::randEngine(randDevice());
std::uniform_int_distribution<int> rnd::dist(0, 100);

long long rnd::randInt(){
	long long base = dist(randEngine);
	long long time = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	return base + time;
}

int rnd::iRange(int low, int high){
	if (low > high){
		int temp = low;
		low = high;
		high = temp;
	}
	if (low == high){
		return low;
	}
	long long val = dist(randEngine);
	val += std::chrono::high_resolution_clock::now().time_since_epoch().count();
	return (val%((high-low)+1))+low;
}
bool rnd::roll(int upper){
	return iRange(0, upper)==1;
}

