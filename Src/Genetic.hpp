#include"Kuliah.hpp"
#include"Ruang.hpp"
#include "RandomGenerator.hpp"

#ifndef GENETIC_HPP
#define GENETIC_HPP

static const int N_DAY = 5;
static const int N_TIME = 11;
static const char FIRST_CHAR = 'a';
static const int DELTA_TIME = 7;
static const int DELTA_DAY = 1;
static const int SLOTFITNESSMAX = 4;

class Genetic {
    private :
        Ruang ** rooms;
        Kuliah ** courses;
        string * solutionSample;
        int nRuang;
        int nKuliah;
        int nSample;
        RandomGenerator* R;

        string bestSolution;
        int bestConflict;

    public :
        Genetic(Ruang **, Kuliah**, int, int, int);
        ~Genetic();

        int getRoom(string, int);
        int getDay(string, int);
        int getStartTime(string, int);
        int getEndTime(string, int);

        int nSlotConflict(string, int, int, int);
        int nCourseConflict(string, int);
        int nScheduleConflict(string);

        int roomNametoInt(string);

        string randString();
        void geneticInit();

        int fitnessFunc(string);
        void geneticSelection();

        void pairString(int*);
        void cross(string*, int, int);
        void geneticCrossover();

        void mutateString(string*);
        void geneticMutation();

        void eval();
        void solveGA(int);

        string getSolutionRoom(int);
        int getSolutionDay(int);
        int getSolutionStartTime(int);
};

Genetic :: Genetic(Ruang** room, Kuliah** course, int n, int nrooms, int ncourses) {
    rooms = room;
    courses = course;
    nSample = n;
    nRuang = nrooms;
    nKuliah = ncourses;
    solutionSample = new string[nSample];
    R = new RandomGenerator();
    bestConflict = nRuang*nKuliah*N_DAY*N_TIME;
}

Genetic :: ~Genetic() {
    delete solutionSample;
    delete R;
}

int Genetic :: getRoom(string schedule, int courseID) {
    return (int)(schedule[4*courseID + 0]) - (int)'a';
}

int Genetic :: getDay(string schedule, int courseID) {
    return (int)(schedule[4*courseID + 1]) - (int)'a';
}

int Genetic :: getStartTime(string schedule, int courseID) {
    return (int)(schedule[4*courseID + 2]) - (int)'a';
}

int Genetic :: getEndTime(string schedule, int courseID) {
    return (int)(schedule[4*courseID + 3]) - (int)'a';
}

int Genetic :: nSlotConflict(string schedule, int room, int day, int time) {
    int conflictCount = -1;
    for (int i = 0; i < nKuliah; i++) {
        if ((int) getRoom(schedule, i) == room
                && getDay(schedule, i) == day
                && getStartTime(schedule, i) <= time
                && getEndTime(schedule, i) >= time) {
            conflictCount++;
        }
    }
    return conflictCount;
}

int Genetic :: nCourseConflict(string schedule, int courseID) {
    int conflictCount = 0;
    for ( int i = getStartTime(schedule, courseID) ; i<=getEndTime(schedule, courseID); i++){
        conflictCount += nSlotConflict(schedule, getRoom(schedule, courseID), getDay(schedule, courseID), i);
    }
    return conflictCount;
}

int Genetic :: nScheduleConflict(string schedule) {
    int conflictCount = 0;
    for (int i = 0; i < nRuang; i++) {
        for (int j = 0; j < N_DAY; j++) {
            for (int k = 0; k < N_TIME; k++) {
                if (nSlotConflict(schedule, i, j, k) > 0) {
                    conflictCount += nSlotConflict(schedule, i, j, k);
                }
            }
        }
    }
    return conflictCount;
}

int Genetic :: roomNametoInt(string roomname) {
    bool found = false;
    int i=0;
    while (i < nRuang && !found) {
        if (rooms[i] -> getName() == roomname) {
            found = true;
        } else {
            i++;
        }
    }
    return i;
}

string Genetic :: randString() {
    string s = "";
    int slotSpace[nRuang][N_DAY][N_TIME];
    int slotCount;
    for (int i = 0; i < nKuliah; i++) {
        slotCount = 0;
        int roomIdx;
        if (courses[i] -> isButuhRuang()) {
            roomIdx = roomNametoInt(courses[i] -> getButuhRuang());
        } else {
            roomIdx = -1;
        }
        for (int r = 0; r < nRuang; r++) {
            for (int d = 0; d < N_DAY; d++) {
                for (int t = 0; t < N_TIME; t++) {
                    if ((roomIdx < 0 || r == roomIdx)
                          && courses[i] -> isDayAvail(d+DELTA_DAY)
                          && rooms[r] -> isDayAvail(d+DELTA_DAY)
                          && courses[i] -> isTimeAvail(t + DELTA_TIME, t + DELTA_TIME + courses[i] -> getDuration())
                          && rooms[r] -> isTimeAvail(t + DELTA_TIME, t + DELTA_TIME + courses[i] -> getDuration())){

                        slotSpace[r][d][t] = 1;
                    } else {
                        slotSpace[r][d][t] = 0;
                    }
                    slotCount+= slotSpace[r][d][t];
                }
            }
        }

        int temp = R -> nextInt(slotCount);
        int sum = 0;
        int r, d, t;
        for (r = 0 ; sum <= temp && r < nRuang; r++) {
            for (d = 0; sum <= temp && d < N_DAY; d++) {
                for (t = 0;sum <= temp && t < N_TIME; t++) {
                    sum += slotSpace[r][d][t];
                }
            }
        }
        s += (char)((int)'a' + r - 1);
        s += (char)((int)'a' + d - 1);
        s += (char)((int)'a' + t - 1);
        s += (char)((int)'a' + t + courses[i] -> getDuration() - 1 - 1);
    }
    return s;
}

void Genetic :: geneticInit() {
    string sampleCollection[nSample];

    for (int i = 0; i < nSample; i++) {
        string temp;
        bool samplePicked = false;
        while(!samplePicked) {
            temp = randString();
            bool found = false;
            for (int j = 0; j < i; j++) {
                if (sampleCollection[i] == sampleCollection[j]) {
                    found = true;
                }
            }
            samplePicked = !found;
        }
        sampleCollection[i] = temp;
    }

    for (int i = 0; i < nSample; i++) {
        solutionSample[i] = sampleCollection[i];
    }
}

int Genetic :: fitnessFunc(string schedule) {
    int sum = 0;
    for (int r = 0; r < nRuang; r++) {
        for (int d = 0; d < N_DAY; d++) {
            for ( int t = 0; t < N_TIME; t++) {
                if (nSlotConflict(schedule, r, d, t) >= 0) {
                    int temp = SLOTFITNESSMAX - nSlotConflict(schedule, r, d, t);
                    if (temp > 0) {
                        sum += temp;
                    }
                }
            }
        }
    }
    return sum;
}

void Genetic :: geneticSelection() {
    int sum = 0;

    string ret[nSample];
    int probabilityTable[nSample];

    for (int i = 0; i < nSample; i++) {
        probabilityTable[i] = sum + fitnessFunc(solutionSample[i]);
        sum = probabilityTable[i];
    }

    int temp;

    for (int i = 0; i < nSample; i++) {
        temp = R -> nextInt(sum);
        int j;
        for (j = 0; temp >= probabilityTable[j]; j++) {
            //do nothing
        }
        ret[i] = solutionSample[j];
    }

    for (int i = 0; i < nSample; i++) {
        solutionSample[i] = ret[i];
    }
}

void Genetic :: pairString(int* pairTable) {

    int pairPtr = 0;

    for (int i = 0; i < nSample; i++) {
        pairTable[i] = -1;
    }
    for (int pairCount = 0; pairCount < nSample/2; pairCount++) {
        int temp = R -> nextInt(nSample-2*pairCount-1);
        int tempPtr = pairPtr+1;
        while (pairTable[tempPtr] != -1 || temp != 0) {
            if (pairTable[tempPtr] == -1) {
                temp--;
            }
            tempPtr++;
        }
        pairTable[pairPtr] = tempPtr;
        pairTable[tempPtr] = pairPtr;
        bool found = false;
        while (pairPtr < nKuliah && !found) {
            if (pairTable[pairPtr] == -1) {
                found = true;
            } else {
                pairPtr++;
            }
        }
    }
}

void Genetic :: cross(string* s, int s1, int s2) {
    int crossTable[nKuliah];

    for(int i = 0; i < nKuliah; i++) {
        if (nScheduleConflict(s[s1]) + nScheduleConflict(s[s2]) != 0) {
            int temp = R -> nextInt(nScheduleConflict(s[s1]) + nScheduleConflict(s[s2]));
            if (temp < nCourseConflict(s[s1], i) + nCourseConflict(s[s2],i)) {
                crossTable[i] = 1;
            } else {
                crossTable[i] = 0;
            }
        } else {
            crossTable[i] = 0;
        }

    }
    for (int i = 0; i < nKuliah; i++) {
        if (crossTable[i] == 1) {
            for(int j = 0; j < 4; j++) {
                char temp = s[s1][4*i+j];
                s[s1][4*i+j] = s[s2][4*i+j];
                s[s2][4*i+j] = temp;
            }
        }
    }
}

void Genetic :: geneticCrossover() {
    string ret[nSample];
    for (int i = 0; i < nSample; i++) {
        ret[i] = solutionSample[i];
    }

    int* pairTable = new int[nSample];
    pairString(pairTable);

    int crossPtr = 0;

    while(crossPtr < nSample) {
        cross(ret, crossPtr, pairTable[crossPtr]);
        pairTable[pairTable[crossPtr]] = -1;
        pairTable[crossPtr] = -1;
        bool found = false;
        while(crossPtr < nSample && !found) {
            if (pairTable[crossPtr] != -1) {
                found = true;
            } else {
                crossPtr++;
            }
        }
    }
    for (int i = 0; i < nSample; i++) {
        solutionSample[i] = ret[i];
    }
}

void Genetic :: mutateString(string* schedule) {

    char mutateTable[nKuliah][4];
    int slotSpace[nRuang][N_DAY][N_TIME];
    if ((nScheduleConflict(*schedule)) != 0) {
        for(int i = 0; i < nKuliah; i++){
            int temp = R -> nextInt(nScheduleConflict(*schedule));
            int slotCount = 0;
            if (temp < nCourseConflict(*schedule, i)) {
                int roomIdx;
                if (courses[i] -> isButuhRuang()) {
                    roomIdx = roomNametoInt(courses[i] -> getButuhRuang());
                } else {
                    roomIdx = -1;
                }

                for (int r = 0; r < nRuang; r++) {
                    for (int d = 0; d < N_DAY; d++) {
                        for (int t = 0; t < N_TIME; t++) {
                            if ((roomIdx < 0 || r == roomIdx)
                                  && courses[i] -> isDayAvail(d+DELTA_DAY)
                                  && rooms[r] -> isDayAvail(d+DELTA_DAY)
                                  && courses[i] -> isTimeAvail(t + DELTA_TIME, t + DELTA_TIME + courses[i] -> getDuration())
                                  && rooms[r] -> isTimeAvail(t + DELTA_TIME, t + DELTA_TIME + courses[i] -> getDuration())){
                                slotCount++;
                                slotSpace[r][d][t] = 1;
                            } else {
                                slotSpace[r][d][t] = 0;
                            }
                        }
                    }
                }
                int temp2 = R -> nextInt(slotCount);
                int sum = 0;
                int r, d, t;
                for (r = 0 ; sum <= temp2 && r < nRuang; r++) {
                    for (d = 0 ; sum <= temp2 && d < N_DAY; d++) {
                        for (t = 0 ; sum <= temp2 && t < N_TIME; t++) {
                            sum += slotSpace[r][d][t];
                        }
                    }
                }
                mutateTable[i][0] = (char)((int)'a' + r - 1);
                mutateTable[i][1] = (char)((int)'a' + d - 1);
                mutateTable[i][2] = (char)((int)'a' + t - 1);
                mutateTable[i][3] = (char)((int)'a' + t + courses[i] -> getDuration() - 1 - 1);
            } else {
                mutateTable[i][0] = '-';
                mutateTable[i][1] = '-';
                mutateTable[i][2] = '-';
                mutateTable[i][3] = '-';
            }
        }
        for (int i = 0; i < nKuliah; i++) {
            if (mutateTable[i][0] != '-') {
                (*schedule)[4*i] = mutateTable[i][0];
                (*schedule)[4*i+1] = mutateTable[i][1];
                (*schedule)[4*i+2] = mutateTable[i][2];
                (*schedule)[4*i+3] = mutateTable[i][3];
            }
        }
    }
}

void Genetic :: geneticMutation() {
    for (int i = 0; i < nSample; i++) {
        mutateString(&(solutionSample[i]));
    }
}

void Genetic :: eval() {
    int currentBestConflict;
    int currentBestIdx;
    int currentConflict;
    for (int i = 0; i < nSample; i++) {
        if (i == 0) {
            currentBestConflict = nScheduleConflict(solutionSample[i]);
            currentBestIdx = i;
        } else {
            currentConflict = nScheduleConflict(solutionSample[i]);
            if (currentConflict < currentBestConflict) {
                currentBestConflict = currentConflict;
                currentBestIdx = i;
            }
        }
    }
    if (currentBestConflict < bestConflict) {
        bestSolution = solutionSample[currentBestIdx];
        bestConflict = currentBestConflict;
    }
}


void Genetic :: solveGA(int nCycle) {
    geneticInit();
    geneticSelection();
    eval();
    for(int i = 0; i < nCycle && bestConflict != 0; i++) {
        geneticCrossover();
        eval();
        if (bestConflict != 0) {
            geneticMutation();
        }

    }

    int best, bestIdx;
    for(int i = 0; i<nSample; i++) {
        if (i == 0) {
            best = nScheduleConflict(solutionSample[i]);
            bestIdx = i;
        } else {
            int temp = nScheduleConflict(solutionSample[i]);
            if (temp < best) {
                best = temp;
                bestIdx = i;
            }
        }
    }
    bestSolution = solutionSample[bestIdx];
}

string Genetic :: getSolutionRoom(int courseID) {
    return rooms[(int)(bestSolution[4*courseID + 0]) - (int)'a'] -> getName();
}

int Genetic :: getSolutionDay(int courseID) {
    return (int)(bestSolution[4*courseID + 1]) - (int)'a' + DELTA_DAY;
}

int Genetic :: getSolutionStartTime(int courseID) {
    return (int)(bestSolution[4*courseID + 2]) - (int)'a' + DELTA_TIME;
}
#endif
