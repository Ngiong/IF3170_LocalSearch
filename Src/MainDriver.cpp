#include <bits/stdc++.h>
#include "Problem.hpp"
using namespace std;

int main() {
	Problem n;
	string file;
	
	cout << "********************" << endl;
	cout << "*** LOCAL SEARCH ***" << endl;
	cout << "********************" << endl << endl;
	//cout << "Masukkan testcase: "; cin >> file;
	//n.fileToVar(file);

	//cout << "yolo" << endl;
	n.solveUsingSA(1, 0.01, 10, 100);
	//n.solveUsingHill();
	int count = n.countConflictCourses();
	cout << "CONFLICT : " << count << endl;
	
	return 0;
}

