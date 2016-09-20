#ifndef KULIAH_HPP
#define KULIAH_HPP

#include <bits/stdc++.h>
using namespace std;

class Kuliah {
	friend class Problem;
	public :
		// ctor
		Kuliah();
		Kuliah(string, string, int, int, int, bool, bool, bool, bool, bool);
		
		// getter, setter
		int getId() { return kuliahId; }
		string getKode() { return kode; }
		string getButuhRuang() { return butuhRuang; }
		int getStartTime() { return start; }
		int getEndTime() { return end; }
		int getDuration() { return duration; }
		string getCurrentRuang() { return currentRuang; }
		int getCurrentStartTime() { return currentStartTime; }
		
		// predikat
		bool isButuhRuang() { return (butuhRuang != "-"); }
		bool isDayAvail(int i) { return days[i]; }
		bool isTimeAvail(int b, int e) {
			return (start <= b && b <= end && start <= e && e <= end);
		}
		bool isAvailable(int day, int b, int e) { return isDayAvail(day) && isTimeAvail(b, e); }
		
	private :
		static int lastKuliahId;
		int kuliahId;
		string kode;
		string butuhRuang;
		int start, end;
		int duration;
		bool days[8];
			
		string currentRuang;
		int currentStartTime, currentDay;
};

int Kuliah::lastKuliahId = 0;

Kuliah::Kuliah() {
	kuliahId = ++lastKuliahId;
	kode = "-"; butuhRuang = "-";
	start = 7; end = 18; duration = 1;
	for(int i=1; i<=5; i++) {
		days[i] = 1;	
	}
}

Kuliah::Kuliah(string k, string br, int s, int e, int d, bool d1, bool d2, bool d3, bool d4, bool d5) {
	kuliahId = ++lastKuliahId;
	kode = k; butuhRuang = br;
	start = s; end = e; duration = d;
	days[1] = d1; days[2] = d2; days[3] = d3; 
	days[4] = d4; days[5] = d5;
}

#endif

