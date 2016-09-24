#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <bits/stdc++.h>
#include "Kuliah.hpp"
#include "Ruang.hpp"
#include "RandomGenerator.hpp"
using namespace std;

class Problem {
	public :
		Problem();
		Problem(int, int);
		Problem(const Problem &P);
		~Problem();
		Problem& operator= (const Problem &P);
		
		// Solver
		void solveUsingHill();
		void solveUsingSA(double, double, int, int);
		void solveUsingGA();
		void solveUsingKocokan(int); // maxSteps
		Problem modifySolution(Problem P);
		Problem modifySolutionHill(Problem P);
		
		// Init
		void initByRandom();
		void initByMikir(); /* ================== BERHARAP BANYAK DENGAN METHOD INI ==========================*/
		// Salah satu yg bisa dipertimbangkan untuk initByMikir adalah menjadikan sebuah matrix terlebih dahulu, 
		// lalu melakukan assignment u/ slot-slot yang hanya mungkin di occupy oleh 1 matakuliah
		
		// Performance Measure
		bool isSolved();
		int countConflictCourses();
		
	private :
		int nRooms, nCourses;
		Ruang ** room;
		Kuliah ** course;
		RandomGenerator rnd;
};

Problem::Problem() {
	nRooms = 4; nCourses = 8;
	room = new Ruang * [4];
	room[0] = new Ruang("7602", 7, 14, 1,1,1,1,1); // perhatikan kalau kita maunya 1-based index u/ array
	room[1] = new Ruang("7603", 7, 14, 1,0,1,0,1);
	room[2] = new Ruang("7610", 9, 12, 1,1,1,1,1);
	room[3] = new Ruang("Labdas2", 10, 14, 0,1,0,1,0);
	course = new Kuliah * [8];
	course[0] = new Kuliah("IF2110", "7602", 7, 12, 4, 1,1,1,1,1);
	course[1] = new Kuliah("IF2130", "-",   10, 16, 3, 0,0,1,1,0);
	course[2] = new Kuliah("IF2150", "-",    9, 13, 2, 1,0,1,0,1);
	course[3] = new Kuliah("IF2170", "7610", 7, 12, 3, 1,1,1,1,1);
	course[4] = new Kuliah("IF3110", "7602", 7,  9, 2, 1,1,1,1,1);
	course[5] = new Kuliah("IF3130", "-",    7, 12, 2, 0,0,1,1,1);
	course[6] = new Kuliah("IF3170", "7602", 7,  9, 2, 1,1,1,1,1);
	course[7] = new Kuliah("IF3111", "-",    7, 12, 2, 1,1,1,1,1);
}

// Ntar dikasih fitur untuk nge-parse juga dari file
Problem::Problem(int nRuang, int nKuliah) {
	nRooms = nRuang; nCourses = nKuliah;
	room = new Ruang * [nRuang];
	course = new Kuliah * [nKuliah];
	/******************************************
	*    Edit2 Spek Ruang dan Kuliah di sini
	*******************************************/
	// cout << rooms[1].ruangName << endl; // Bisa karena sudah di FRIEND kan biar gampang gitchuuu :v
}

Problem::Problem(const Problem &P) {
	nRooms = P.nRooms; nCourses = P.nCourses;
	room = new Ruang * [nRooms];
	course = new Kuliah * [nCourses];
	
	for(int i = 0; i < nRooms; i++) {
		room[i] = P.room[i];
	}
	for(int i = 0; i < nCourses; i++) {
		course[i] = P.course[i];
	}
}

Problem::~Problem() {
	delete [] room;
	delete [] course;	
}

Problem& Problem::operator= (const Problem &P) {
	nRooms = P.nRooms; nCourses = P.nCourses;
	room = new Ruang * [nRooms];
	course = new Kuliah * [nCourses];
	
	for(int i = 0; i < nRooms; i++) {
		room[i] = P.room[i];
	}
	for(int i = 0; i < nCourses; i++) {
		course[i] = P.course[i];
	}	
	return *this;
}

/*********************************************
**				VARIABLE INITIATOR
**
**********************************************/
void Problem::initByRandom() {
	for(int i=0; i<nCourses; i++) {
		// Set Waktu
		int randomlyChosenRoomIdx;
		int randomlyChosenDay, randomlyChosenStartTime;
		do {
			// Set Ruangan
			if(course[i]->isButuhRuang()) {
				int calonRuangId[200];
				int k = 0;
				for(int j=0; j<nRooms; j++) {
					if(course[i]->butuhRuang == room[j]->ruangName) {
						calonRuangId[k] = j;
						k++;
					}
				}
				randomlyChosenRoomIdx = calonRuangId[rnd.nextInt(k)];
			}
			else {
				randomlyChosenRoomIdx = rnd.nextInt(nRooms);	
			}
			course[i]->currentRuangIdx = randomlyChosenRoomIdx;
			course[i]->currentRuang = room[randomlyChosenRoomIdx]->ruangName;
		

			// * Set hari dulu
			do {
				randomlyChosenDay = rnd.nextInt(1, 5);	
			} while(!course[i]->isDayAvail(randomlyChosenDay));
			course[i]->currentDay = randomlyChosenDay; 
			// Sayangnya : ini bisa kebobol kalo Ruangannya ga available
			// Tapi itulah LOCAL SEARCH, sering dibiarin aja salah duluan, ntar akhir2nya jadi bener...
			
			// * Set waktu
			int courseBegin = course[i]->getStartTime(), 
				courseEnd = course[i]->getEndTime(), 
				courseDuration = course[i]->getDuration();
			randomlyChosenStartTime = rnd.nextInt(courseBegin, courseEnd-courseDuration);
			course[i]->currentStartTime = randomlyChosenStartTime;
			// Tidak perlu di do..while karena random nya PASTI masuk di range courseBegin dan courseEnd
		} while (!room[randomlyChosenRoomIdx]->isTimeAvail(course[i]->currentStartTime, course[i]->currentStartTime + course[i]->duration)
				|| !room[randomlyChosenRoomIdx]->isDayAvail(randomlyChosenDay));
		// do while sampe dapet Ruang yang available;
		
		
		// ** Bisa juga alternatifnya, set hari dan waktu bersamaan
	}
}

/*********************************************
**				PROBLEM SOLVER
**
**********************************************/
void Problem::solveUsingKocokan(int maxSteps) {
	initByRandom();
	
	int stepCounter = 0;
	while(!isSolved() && stepCounter++ < maxSteps) {
		// Pilih variabel yg conflict
		int randomlySelectedVariable = rnd.nextInt(nCourses); 
		// ** gebleknya.. krn ga kepikiran isConflictingVariable nya gimana implementasinya
		
		// Set ulang secara randomly
		// ** Yg modif adalah : ruangannya, harinya
		// ** Jam kuliah akan menyesuaikan dengan randomize
		if(course[randomlySelectedVariable]->isButuhRuang()) { // PASTI HARINYA
			int randomlyChosenDay;
			do {
				randomlyChosenDay = rnd.nextInt(1, 5);	
			} while(!course[randomlySelectedVariable]->isDayAvail(randomlyChosenDay));
			course[randomlySelectedVariable]->currentDay = randomlyChosenDay;
		}
		
		// Measure performance
		// *********************** Save it for later ***********************
	}
	// isSolved() OR stepCounter >= maxSteps
	if(stepCounter < maxSteps) cout << "YAY" << endl;
	else cout << "NAH" << endl;
	
	for(int i=0; i<nCourses; i++) {
		cout << *course[i] << endl;	
	}
}

void Problem::solveUsingSA(double temperature, double descentRate, int n, int maxSteps) {
	initByRandom();
	for(int i=0; i<nCourses; i++) {
			cout << *course[i] << endl;	
		}

	int stepCounter = 0;
	Problem tempSolution = *this;
	int tempEvalValue = countConflictCourses();

	while(tempEvalValue > 0 && stepCounter++ < maxSteps) {
		for(int i = 0; i < n; i++) {
			tempSolution = modifySolution(*this);
			int newEvalValue = tempSolution.countConflictCourses();
			int deltaEval = newEvalValue - tempEvalValue;
			if(deltaEval < 0) {
				*this = tempSolution;
				tempEvalValue = countConflictCourses();
			} else if (exp(-deltaEval/temperature) > rnd.nextDouble()) {
				*this = tempSolution;
				tempEvalValue = countConflictCourses();
			}
			cout << "step : " << (stepCounter-1)*10+i << " conflict : " << tempEvalValue << endl;
			if(tempEvalValue == 0) break;
		}
		temperature -= descentRate;

	}
	for(int i=0; i<nCourses; i++) {
		cout << *course[i] << endl;	
	}
}

void Problem::solveUsingHill() {
	int stepCounter;
	Problem tempSolution = *this;
	int tempEvalValue;
	int newEvalValue;
	bool isLocalMaxima;

	do {
		cout << "Restart" << endl;
		initByRandom();
		for(int i=0; i<nCourses; i++) {
			cout << *course[i] << endl;	
		}
		stepCounter = 0;
		tempEvalValue = countConflictCourses();
		cout << "step : 0 conflict : " << tempEvalValue << endl;
		isLocalMaxima = false;
		while(isLocalMaxima == false && tempEvalValue>0) {
			tempSolution = modifySolution(*this);
			newEvalValue = tempSolution.countConflictCourses();
			if (newEvalValue <= tempEvalValue) {
				*this = tempSolution;
				tempEvalValue = countConflictCourses();
				stepCounter++;
				cout << "step : " << stepCounter << " conflict : " << tempEvalValue << endl;
			}
			else {
				isLocalMaxima = true;
				cout << "conflict terpilih: " << newEvalValue << ", tidak diterima" << endl; 
			}
		}
	} while (tempEvalValue>0);
	for(int i=0; i<nCourses; i++) {
		cout << *course[i] << endl;	
	}
}

Problem Problem::modifySolution(Problem P) {
	int randomlyChosenCourse = P.rnd.nextInt(nCourses);
	int randomlyChosenRoomIdx;
	int randomlyChosenDay, randomlyChosenStartTime;
//	cout << "course diubah " << randomlyChosenCourse << endl;
	do {
		// Set Ruangan
		if(P.course[randomlyChosenCourse]->isButuhRuang()) {
			int calonRuangId[200];
			int k = 0;
			for(int j=0; j<nRooms; j++) {
				if(P.course[randomlyChosenCourse]->butuhRuang == P.room[j]->ruangName) {
					calonRuangId[k] = j;
					k++;
				}
			}
			randomlyChosenRoomIdx = calonRuangId[rnd.nextInt(k)];
		}
		else {
			randomlyChosenRoomIdx = rnd.nextInt(nRooms);
		}
		P.course[randomlyChosenCourse]->currentRuangIdx = randomlyChosenRoomIdx;
		P.course[randomlyChosenCourse]->currentRuang = room[randomlyChosenRoomIdx]->ruangName;
	
		// * Set hari dulu
		do {
			randomlyChosenDay = P.rnd.nextInt(1, 5);	
		} while(!P.course[randomlyChosenCourse]->isDayAvail(randomlyChosenDay));
		P.course[randomlyChosenCourse]->currentDay = randomlyChosenDay; 
		// Sayangnya : ini bisa kebobol kalo Ruangannya ga available
		// Tapi itulah LOCAL SEARCH, sering dibiarin aja salah duluan, ntar akhir2nya jadi bener...
		
		// * Set waktu
		int courseBegin = P.course[randomlyChosenCourse]->getStartTime(), 
			courseEnd = P.course[randomlyChosenCourse]->getEndTime(), 
			courseDuration = P.course[randomlyChosenCourse]->getDuration();
		randomlyChosenStartTime = P.rnd.nextInt(courseBegin, courseEnd-courseDuration);
		P.course[randomlyChosenCourse]->currentStartTime = randomlyChosenStartTime;
		// Tidak perlu di do..while karena random nya PASTI masuk di range courseBegin dan courseEnd
	} while (!P.room[randomlyChosenRoomIdx]->isTimeAvail(P.course[randomlyChosenCourse]->currentStartTime,
			P.course[randomlyChosenCourse]->currentStartTime + P.course[randomlyChosenCourse]->duration)
			|| !room[randomlyChosenRoomIdx]->isDayAvail(randomlyChosenDay));
	return P;
}

/*********************************************
**			 PERFORMANCE MEASURE
**
**********************************************/
bool Problem::isSolved() {
	int randomlyIsSolved = rnd.nextInt(1, 100);
	if(randomlyIsSolved < 3) return 1; // 2% Solved , geblek bangettt
	else return 0;
}

int Problem::countConflictCourses() {
	int count = 0;
	
	for(int i=0; i<nCourses-1; i++) {
		for(int j=i+1; j<nCourses; j++) {
			if(course[i]->currentRuang == course[j]->currentRuang) {
				if(course[i]->currentDay == course[j]->currentDay) {
					int maks, minim;
					maks = max(course[i]->currentStartTime, course[j]->currentStartTime);
					minim = min(course[i]->currentStartTime + course[i]->getDuration(),
								course[j]->currentStartTime + course[j]->getDuration());
					// tambah sesuai banyaknya jam yang bentrok
					if(maks <= minim) {
						count += minim - maks;
					}
				}
			}
		}
	}
	return count;
}
#endif
