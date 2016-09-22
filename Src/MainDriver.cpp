#include <bits/stdc++.h>
#include "Problem.hpp"
using namespace std;

int main() {
	Problem n;
	
	n.solveUsingSA(1, 0.01, 10, 100);
	int count = n.countConflictCourses();
	cout << count << endl;
	return 0;
}

