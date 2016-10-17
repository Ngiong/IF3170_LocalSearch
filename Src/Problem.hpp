#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <bits/stdc++.h>
#include "Kuliah.hpp"
#include "Ruang.hpp"
#include "RandomGenerator.hpp"
#include "Genetic.hpp"
using namespace std;

class Problem {
	public :
		Problem();
		Problem(string file);
		Problem(const Problem &P);
		~Problem();
		Problem& operator= (const Problem &P);

		// Solver
		void solveUsingHill(int maxRestart);
		void solveUsingSA(double, double, int, int);
		void solveUsingGA(int, int);
		Problem modifySolution(Problem P);

		// Init
		void initByRandom();

		// Performance Measure
		bool isSolved();
		int countConflictCourses();
		int getAvailableDuration(string);	
		
		Ruang& getRuang(int i){
			return *room[i];
		}
		
		Kuliah& getKuliah(int i){
			return *course[i];
		}
		
		int getNRoom() {
			return nRooms;
		}
		
		int getNCourse(){
			return nCourses;
		}
		
	private :
		int nRooms, nCourses;
		Ruang ** room;
		Kuliah ** course;
		RandomGenerator rnd;
};

Problem::Problem() {
	nRooms = 0; nCourses = 0;
	room = new Ruang * [0];
	course = new Kuliah * [0];
}

Problem::Problem(string file) {
	string line;
	nRooms = nCourses = 0;

	ifstream myfile(file);
	// identify jumlah ruang dan jadwal
	if (myfile.is_open()) {
		getline(myfile, line);
		while (line != "Jadwal") {
			nRooms++;
			getline(myfile, line);
		}
		nRooms -= 2;
		while (getline(myfile, line)) {
			nCourses++;
		}
		myfile.close();

		room = new Ruang * [nRooms];
		course = new Kuliah * [nCourses];
	}
	else {
		cout << "Unable to open file." << endl;
	}

	// masukkan info file ke var
	myfile.open(file);
	if (myfile.is_open()) {
		getline(myfile, line);
		string ruangan, jadwal;
		int startTime, finishTime, durasi;
		bool isSenin, isSelasa, isRabu, isKamis, isJumat;
 		// masukin info ruangan
		int j;
		for (int i=0; i<nRooms; i++) {
			ruangan = "";
			startTime = finishTime = 0;
			isSenin = isSelasa = isRabu = isKamis = isJumat = false;
			getline(myfile, line);
			j = 0;
			while (line[j] != ';') {
				ruangan = ruangan + line[j];
				j++;
			}
			j++;
			while (line[j] != '.') {
				startTime = startTime*10 + (line[j]-48);
				j++;
			}
			j+=4;
			while (line[j] != '.') {
				finishTime = finishTime*10 + (line[j]-48);
				j++;
			}
			j+=4;
			while (j<line.length()) {
				if (line[j] == '1') {
					isSenin = true;
				}
				else if (line[j] == '2') {
					isSelasa = true;
				}
				else if (line[j] == '3') {
					isRabu = true;
				}
				else if (line[j] == '4') {
					isKamis = true;
				}
				else if (line[j] == '5') {
					isJumat = true;
				}
 				j++;
			}
			room[i] = new Ruang(ruangan, startTime, finishTime, isSenin, isSelasa, isRabu, isKamis, isJumat);
		}

		// masukin info jadwal
		getline(myfile, line);
		getline(myfile, line);
		for (int i=0; i<nCourses; i++) {
			ruangan = jadwal = "";
			startTime = finishTime = durasi = 0;
			isSenin = isSelasa = isRabu = isKamis = isJumat = false;
			getline(myfile, line);
			j = 0;
			while (line[j] != ';') {
				jadwal = jadwal + line[j];
				j++;
			}
			j++;
			while (line[j] != ';') {
				ruangan = ruangan + line[j];
				j++;
			}
			j++;
			while (line[j] != '.') {
				startTime = startTime*10 + (line[j]-48);
				j++;
			}
			j+=4;
			while (line[j] != '.') {
				finishTime = finishTime*10 + (line[j]-48);
				j++;
			}
			j+=4;
			while (line[j] != ';') {
				durasi = durasi*10 + (line[j]-48);
				j++;
			}
			j++;
			while (j<line.length()) {
				if (line[j] == '1') {
					isSenin = true;
				}
				else if (line[j] == '2') {
					isSelasa = true;
				}
				else if (line[j] == '3') {
					isRabu = true;
				}
				else if (line[j] == '4') {
					isKamis = true;
				}
				else if (line[j] == '5') {
					isJumat = true;
				}
 				j++;
			}
			course[i] = new Kuliah(jadwal, ruangan, startTime, finishTime, durasi, isSenin, isSelasa, isRabu, isKamis, isJumat);
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file." << endl;
	}
}

Problem::Problem(const Problem &P) {
	nRooms = P.nRooms; nCourses = P.nCourses;
	room = new Ruang * [nRooms];
	course = new Kuliah * [nCourses];

	for(int i = 0; i < nRooms; i++) {

		room[i] = new Ruang(P.room[i]->ruangName, P.room[i]->startHours, P.room[i]->endHours,
					P.room[i]->availDays[1], P.room[i]->availDays[2], P.room[i]->availDays[3], P.room[i]->availDays[4], P.room[i]->availDays[5]);
	}
	for(int i = 0; i < nCourses; i++) {

		course[i] = new Kuliah(P.course[i]->kode, P.course[i]->butuhRuang, P.course[i]->start, P.course[i]->end, P.course[i]->duration,
					P.course[i]->days[1], P.course[i]->days[2], P.course[i]->days[3], P.course[i]->days[4], P.course[i]->days[5]);

		course[i]->currentRuang = P.course[i]->currentRuang;
		course[i]->currentRuangIdx = P.course[i]->currentRuangIdx;
		course[i]->currentStartTime = P.course[i]->currentStartTime;
		course[i]->currentDay = P.course[i]->currentDay;
	}
}

Problem::~Problem() {
	delete [] room;
	delete [] course;
}

Problem& Problem::operator= (const Problem &P) {
	delete [] room;
	delete [] course;
	nRooms = P.nRooms; nCourses = P.nCourses;
	room = new Ruang * [nRooms];
	course = new Kuliah * [nCourses];

	for(int i = 0; i < nRooms; i++) {
		room[i] = new Ruang(P.room[i]->ruangName, P.room[i]->startHours, P.room[i]->endHours,
					P.room[i]->availDays[1], P.room[i]->availDays[2], P.room[i]->availDays[3], P.room[i]->availDays[4], P.room[i]->availDays[5]);
	}
	for(int i = 0; i < nCourses; i++) {
		course[i] = new Kuliah(P.course[i]->kode, P.course[i]->butuhRuang, P.course[i]->start, P.course[i]->end, P.course[i]->duration,
					P.course[i]->days[1], P.course[i]->days[2], P.course[i]->days[3], P.course[i]->days[4], P.course[i]->days[5]);

		course[i]->currentRuang = P.course[i]->currentRuang;
		course[i]->currentRuangIdx = P.course[i]->currentRuangIdx;
		course[i]->currentStartTime = P.course[i]->currentStartTime;
		course[i]->currentDay = P.course[i]->currentDay;
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
		cout << "a" << i << "<br>";
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
				cout << "b" << i << "<br>";
				randomlyChosenRoomIdx = calonRuangId[rnd.nextInt(k)];
			}
			else {
				randomlyChosenRoomIdx = rnd.nextInt(nRooms);
			}
			course[i]->currentRuangIdx = randomlyChosenRoomIdx;
			course[i]->currentRuang = room[randomlyChosenRoomIdx]->ruangName;

			// * Set hari
			do {
				cout << "c" << i << "<br>";
				randomlyChosenDay = rnd.nextInt(1, 5);
			} while(!course[i]->isDayAvail(randomlyChosenDay));
			course[i]->currentDay = randomlyChosenDay;

			// * Set waktu
			int courseBegin = course[i]->getStartTime(),
				courseEnd = course[i]->getEndTime(),
				courseDuration = course[i]->getDuration();
			randomlyChosenStartTime = rnd.nextInt(courseBegin, courseEnd-courseDuration);
			course[i]->currentStartTime = randomlyChosenStartTime;
			
		} while ((!room[randomlyChosenRoomIdx]->isTimeAvail(course[i]->currentStartTime, course[i]->currentStartTime + course[i]->duration)
				|| !room[randomlyChosenRoomIdx]->isDayAvail(randomlyChosenDay)
				)&& false);
		cout << i << "<br>";
	}
}

/*********************************************
**				PROBLEM SOLVER
**
**********************************************/
void Problem::solveUsingHill(int maxRestart) {
	int stepCounter, boundLocal, countRestart = 0, minConflict = 999;
	Problem tempSolution;
	Problem minimum;
	int tempEvalValue, newEvalValue;
	bool isLocalMinimum;
	Kuliah ** tempCourse = new Kuliah * [nCourses];

	do {
		cout << "-" << endl;
		initByRandom();
		tempSolution = *this;
		stepCounter = 0;
		boundLocal = 0;
		tempEvalValue = countConflictCourses();
		isLocalMinimum = false;
		while(isLocalMinimum == false && tempEvalValue>0) {
			tempSolution = modifySolution(*this);
			newEvalValue = tempSolution.countConflictCourses();
			if (newEvalValue < tempEvalValue) {
				*this = tempSolution;
				tempEvalValue = countConflictCourses();
				stepCounter++;
			}
			else {
				if (boundLocal <= 500) {
					boundLocal++;
				}
				else {
					isLocalMinimum = true;
				}
			}
		}
		countRestart++;
		if (countConflictCourses() < minConflict) {
			minConflict = countConflictCourses();
			minimum = *this;
		}
	} while (tempEvalValue>0 && countRestart<=maxRestart);
	*this = minimum;
}

void Problem::solveUsingSA(double temperature, double descentRate, int n, int maxSteps) {
	initByRandom();
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
			} else if (exp(-deltaEval/max(0.0,temperature)) > rnd.nextDouble()) {
				*this = tempSolution;
				tempEvalValue = countConflictCourses();
			}
			if(tempEvalValue == 0) break;
		}
		temperature -= descentRate;
	}
}

void Problem :: solveUsingGA(int nSample, int nCycle) {
    Genetic* G = new Genetic(room, course, nSample, nRooms, nCourses);
    G -> solveGA(nCycle);

    for (int  i = 0; i < nCourses; i++) {
        course[i] -> currentRuang = G->getSolutionRoom(i);
        course[i] -> currentRuangIdx = G->getSolutionRoomIdx(i);
        course[i] -> currentDay = G->getSolutionDay(i);
        course[i] -> currentStartTime = G->getSolutionStartTime(i);
    }
    delete G;
}

Problem Problem::modifySolution(Problem P) {
	int randomlyChosenCourse = P.rnd.nextInt(nCourses);
	int randomlyChosenRoomIdx;
	int randomlyChosenDay, randomlyChosenStartTime;
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

		// * Set waktu
		int courseBegin = P.course[randomlyChosenCourse]->getStartTime(),
			courseEnd = P.course[randomlyChosenCourse]->getEndTime(),
			courseDuration = P.course[randomlyChosenCourse]->getDuration();
		randomlyChosenStartTime = P.rnd.nextInt(courseBegin, courseEnd-courseDuration);
		P.course[randomlyChosenCourse]->currentStartTime = randomlyChosenStartTime;
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
	if(randomlyIsSolved < 3) return 1;
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
					if(maks <= minim) {
						count += minim - maks;
					}
				}
			}
		}
	}
	return count;
}

int Problem::getAvailableDuration(string NamaRuang){
	int sum = 0;
	for(int i = 0; i<nRooms; i++)
	{
		int count = 0;
		if(NamaRuang == room[i]->ruangName) {
			for(int j = 1; j <= 5; j++){
				if(room[i]->isDayAvail(j))
					count+=1;
			}
		}
		sum += (room[i]->getEndHours() - room[i]->getStartHours()) * count;
	}
	return sum;
}	
#endif
