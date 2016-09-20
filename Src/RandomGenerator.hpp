#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <bits/stdc++.h>
using namespace std;

class RandomGenerator {
	public :
		// ctor
		RandomGenerator();
		
		// member function
		int nextInt(int max) {
			return (rand() % max);
		}
		int nextInt(int lo, int hi) {
			return ((rand() % (hi-lo+1))+lo);	
		}
		
};

RandomGenerator::RandomGenerator() {
	srand (time(NULL));
}

#endif
