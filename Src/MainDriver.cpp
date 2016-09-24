#include <bits/stdc++.h>
#include "Problem.hpp"
using namespace std;

int main() {
	Problem n;
	
	//n.solveUsingSA(1, 0.01, 10, 100);
	n.solveUsingHill();
	int count = n.countConflictCourses();
	cout << "CONFLICT : " << count << endl;
	return 0;
}

