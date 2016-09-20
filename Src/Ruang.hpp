#ifndef RUANG_HPP
#define RUANG_HPP

#include <bits/stdc++.h>
using namespace std;

class Ruang {
	friend class Problem;
	public :
		// ctor
		Ruang();
		Ruang(string, int, int, bool, bool, bool, bool, bool);
		
		// getter, setter
		int getId() { return ruangId; }
		string getName() { return ruangName; }
		int getStartHours() { return startHours; }
		int getEndHours() { return endHours; }
		bool isDayAvail(int i) { return availDays[i]; }
		bool isTimeAvail(int b, int e) {
			return (startHours <= b && b <= endHours && startHours <= e && e <= endHours);
		}
		
		// member function
		bool isAvailable(int day, int b, int e) { return isDayAvail(day) && isTimeAvail(b, e); }
		
	private :
		static int lastRuangId;
		int ruangId;
		string ruangName;
		int startHours, endHours;
		bool availDays[8];
			
};

// Implementasi member function
int Ruang::lastRuangId = 0;

Ruang::Ruang() {
	ruangId = ++lastRuangId;
	ruangName = "-";
	startHours = 7; endHours = 18;
	for(int i=1; i<=5; i++) {
		availDays[i] = 1;
	}
}

Ruang::Ruang(string n, int s, int e, bool d1, bool d2, bool d3, bool d4, bool d5) {
	ruangId = ++lastRuangId;
	ruangName = n;
	startHours = s; endHours = e;
	availDays[1] = d1; availDays[2] = d2; availDays[3] = d3; 
	availDays[4] = d4; availDays[5] = d5;
}

#endif
