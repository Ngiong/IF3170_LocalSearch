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
		~Problem();
		
		// Solver
		void solveUsingHCA();
		void solveUsingSA();
		void solveUsingGA();
		void solveUsingKocokan(int); // maxSteps
		
		// Init
		void initByRandom();
		void initByMikir(); /* ================== BERHARAP BANYAK DENGAN METHOD INI ==========================*/
		// Salah satu yg bisa dipertimbangkan untuk initByMikir adalah menjadikan sebuah matrix terlebih dahulu, 
		// lalu melakukan assignment u/ slot-slot yang hanya mungkin di occupy oleh 1 matakuliah
		
		// Performance Measure
		bool isSolved();
		
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

Problem::~Problem() {
	delete [] room;
	delete [] course;	
}

/*********************************************
**				VARIABLE INITIATOR
**
**********************************************/
void Problem::initByRandom() {
	for(int i=0; i<nCourses; i++) {
		// Set Ruangan
		if(course[i]->isButuhRuang()) course[i]->currentRuang = course[i]->butuhRuang;	
		else {
			int randomlyPickedRoomIdx = rnd.nextInt(nRooms);
			course[i]->currentRuang = room[randomlyPickedRoomIdx]->getName();	
		}
		
		// Set Waktu
		int randomlyChosenDay, randomlyChosenStartTime;
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

/*********************************************
**			 PERFORMANCE MEASURE
**
**********************************************/
bool Problem::isSolved() {
	int randomlyIsSolved = rnd.nextInt(1, 100);
	if(randomlyIsSolved < 3) return 1; // 2% Solved , geblek bangettt
	else return 0;
}

#endif
