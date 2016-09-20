#include <bits/stdc++.h>
#include "RandomGenerator.hpp"
using namespace std;
// Semangat, Ngiong!!

int main() {
	RandomGenerator rnd;
	for(int i=0; i<100; i++) {
		cout << rnd.nextInt(2,6) << endl;
	}
	return 0;
}

