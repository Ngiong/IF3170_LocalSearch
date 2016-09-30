#include <bits/stdc++.h>
#include <map>
#include "getpost.h"
#include "Problem.hpp"
 
using namespace std;

typedef struct {
	string kodekuliah;
	int jammulai;
	int jamselesai;
	int idkuliah;
} Hasil;
 
int main()
{
	map<string,string> Get;
	initializeGet(Get); //notice that the variable is passed by reference!
	cout<<"Content-type: text/html"<<endl<<endl;
	cout<<"<html>"<<endl;
	cout<<"<head>"<<endl;
	cout<<"<title>AI Course Scheduling</title>"<<endl;
	cout<<"<link href=\"drag.css\" rel=\"stylesheet\"/>"<<endl;
	cout<<"</head>"<<endl;
	cout<<"<body>"<<endl;
	cout << "<p><H1 style=\"font-family: Helvetica;color:blue;border-bottom: 1px solid;margin-bottom: 10px;\">COURSE SCHEDULING AI</H1></p>" << endl;
	cout << "<p>Select the Algorithm : </p>" << endl;
	cout<<"<form method=\"get\">"<<endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"HillClimbing\" checked= \"checked\"> Hill Climbing <br>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"SimulatedAnnealing\"> Simulated Annealing <br>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"GeneticAlgorithm\"> Genetic Algorithm <br><br>" << endl;
	cout << "<p>Browse File: <input type=\"file\" name=\"userfile\" /></p>"<<endl;
	cout<<"<input type=\"submit\" value=\"Solve\" style=\"background-color: #0080ff;border: none;color: white;padding: 10px 27px;text-align: center;text-decoration: none;display: inline-block;font-size: 14px;margin: 4px 2px;cursor: pointer;\" />"<<endl;
	cout<<"</form>"<<endl;
 	
	if (Get.find("algo")!=Get.end() && Get.find("userfile")!=Get.end()) {
		string file = Get["userfile"];
		file = "../tc/" + file;
		// Buat testing
		/*
		cout<<"<p>File path that you loaded   : "<<file<<"</p>"<<endl;
		cout<<"<p>Algorithm that you selected : "<<Get["algo"]<<"</p>"<<endl;*/
		Problem n(file);
		if(Get["algo"] == "HillClimbing"){
			n.solveUsingHill(10);
		} else if(Get["algo"] == "SimulatedAnnealing"){
			// n.solveUsingSA(1, 0.01, 10, 120);
			n.solveUsingSA(10, 0.004, 35, 2600);
		} else {
			n.solveUsingGA(64, 100);	
		} 
		
		cout << "<br>" << endl;
		cout << "<h2 class=\"schedule\">Result</h2>" << endl;
		cout << "<br><br>" << endl;
		int T = n.getNRoom();
		// ini buat nampung bentrok nya
		Hasil arrBentrok[n.getNCourse()];
		int bentrokIterator = 0;
		 
		for(int i = 0; i < T; i++){
			string RoomName = n.getRuang(i).getName();			
			cout << "<h3 class=\"schedule\">" << RoomName << "</h3>" << endl;
			Hasil temp[12][6];
			cout << "<div id = \"columns\"> " << endl;
			
			//init array penampung
			temp[0][0].kodekuliah = "Jam / Hari";
			temp[0][0].jammulai = 0;
			temp[0][0].jamselesai = 0;
			temp[0][0].idkuliah = 0;
			temp[0][1].kodekuliah = "Senin";
			temp[0][1].jammulai = 0;
			temp[0][1].jamselesai = 0;
			temp[0][1].idkuliah = 0;
			temp[0][2].kodekuliah = "Selasa";
			temp[0][2].jammulai = 0;
			temp[0][2].jamselesai = 0;
			temp[0][2].idkuliah = 0;
			temp[0][3].kodekuliah = "Rabu";
			temp[0][3].jammulai = 0;
			temp[0][3].jamselesai = 0;
			temp[0][3].idkuliah = 0;
			temp[0][4].kodekuliah = "Kamis";
			temp[0][4].jammulai = 0;
			temp[0][4].jamselesai = 0;
			temp[0][4].idkuliah = 0;
			temp[0][5].kodekuliah = "Jumat";
			temp[0][5].jammulai = 0;
			temp[0][5].jamselesai = 0;
			temp[0][5].idkuliah = 0;
			
			temp[1][0].kodekuliah = "07.00";
			temp[1][0].jammulai = 0;
			temp[1][0].jamselesai = 0;
			temp[1][0].idkuliah = 0;
			temp[2][0].kodekuliah = "08.00";
			temp[2][0].jammulai = 0;
			temp[2][0].jamselesai = 0;
			temp[2][0].idkuliah = 0;
			temp[3][0].kodekuliah = "09.00";
			temp[3][0].jammulai = 0;
			temp[3][0].jamselesai = 0;
			temp[3][0].idkuliah = 0;
			temp[4][0].kodekuliah = "10.00";
			temp[4][0].jammulai = 0;
			temp[4][0].jamselesai = 0;
			temp[4][0].idkuliah = 0;
			temp[5][0].kodekuliah = "11.00";
			temp[5][0].jammulai = 0;
			temp[5][0].jamselesai = 0;
			temp[5][0].idkuliah = 0;
			temp[6][0].kodekuliah = "12.00";
			temp[6][0].jammulai = 0;
			temp[6][0].jamselesai = 0;
			temp[6][0].idkuliah = 0;
			temp[7][0].kodekuliah = "13.00";
			temp[7][0].jammulai = 0;
			temp[7][0].jamselesai = 0;
			temp[7][0].idkuliah = 0;
			temp[8][0].kodekuliah = "14.00";
			temp[8][0].jammulai = 0;
			temp[8][0].jamselesai = 0;
			temp[8][0].idkuliah = 0;
			temp[9][0].kodekuliah = "15.00";
			temp[9][0].jammulai = 0;
			temp[9][0].jamselesai = 0;
			temp[9][0].idkuliah = 0;
			temp[10][0].kodekuliah = "16.00";
			temp[10][0].jammulai = 0;
			temp[10][0].jamselesai = 0;
			temp[10][0].idkuliah = 0;
			temp[11][0].kodekuliah = "17.00";
			temp[11][0].jammulai = 0;
			temp[11][0].jamselesai = 0;
			temp[11][0].idkuliah = 0;
			for(int i = 1; i < 12; i++){
				for(int j = 1; j < 6; j++){
					temp[i][j].kodekuliah = "-";
					temp[i][j].jammulai = 0;
					temp[i][j].jamselesai = 0;
					temp[i][j].idkuliah = 0;
				}
			}
			
			// mulai baca setiap mata kuliah
			for(int j = 0; j < n.getNCourse(); j++){
				if(n.getKuliah(j).getCurrentRuang() == RoomName){
					int k;
					if(n.getKuliah(j).getCurrentDay() == 1)
						k = 1;
					else if(n.getKuliah(j).getCurrentDay() == 2)
						k = 2;
					else if(n.getKuliah(j).getCurrentDay() == 3)
						k = 3;
					else if(n.getKuliah(j).getCurrentDay() == 4)
						k = 4;
					else
						k = 5;
					if(temp[n.getKuliah(j).getCurrentStartTime()-6][k].kodekuliah == "-")
						temp[n.getKuliah(j).getCurrentStartTime()-6][k].kodekuliah = n.getKuliah(j).getKode();
					else {
						arrBentrok[bentrokIterator].kodekuliah = n.getKuliah(j).getKode();
						bentrokIterator++;
					}
					// check duration
					if(n.getKuliah(j).getDuration() > 1) {
						int duration = n.getKuliah(j).getDuration();
						duration -= 1;
						for(int a = n.getKuliah(j).getCurrentStartTime()-6; a <= n.getKuliah(j).getCurrentStartTime()-6 + duration; a++){
							temp[a][k].kodekuliah = n.getKuliah(j).getKode();
							temp[a][k].idkuliah = j+1;
						}
					}
					else
					{
						temp[n.getKuliah(j).getCurrentStartTime()-6][k].idkuliah = j+1;
					}
				}
			}
			
			// nge cout disini 
			for(int b = 0; b < 12; b++){
				if(b == 0){
					for(int c = 0; c < 6; c++){
						int colour = (temp[b][c].idkuliah)*16384;
						if(c == 5){
							cout << "<div class=\"column\" draggable=\"false\"><header style=\"background-color:" << colour << "\">" <<temp[b][c].kodekuliah<<"</header></div>" << endl;
							cout << "<br><br>" << endl;	
						} 
						else 
							cout << "<div class=\"column\" draggable=\"false\"><header style=\"background-color:" << colour << "\">" <<temp[b][c].kodekuliah<<"</header></div>" << endl;
					}
				} 
				else {
					for(int c = 0; c < 6; c++){
						int colour = (temp[b][c].idkuliah)*16384;
						if(c == 0){
							cout << "<div class=\"column\" draggable=\"false\"><header style=\"background-color:" << colour << "\">" <<temp[b][c].kodekuliah<<"</header></div>" << endl;
						} else if(c == 5){
							cout << "<div class=\"column\" draggable=\"true\"><header style=\"background-color:" << colour << "\">" <<temp[b][c].kodekuliah<<"</header></div>" << endl;
							cout << "<br><br>" << endl;	
						} 
						else 
							cout << "<div class=\"column\" draggable=\"true\"><header style=\"background-color:" << colour << "\">" <<temp[b][c].kodekuliah<<"</header></div>" << endl;
					}
				}
			}
		}
		// buat bentrok
		cout << "<h3 class=\"schedule\">Bentrok</h3>" << endl;
		cout << "Jumlah Bentrok " << n.countConflictCourses() << endl;
		if(bentrokIterator >= 1){
			for(int d = 0; d < bentrokIterator; d++){
				cout << "<div class=\"column\" draggable=\"true\"><header>"<<arrBentrok[d].kodekuliah<<"</header></div>" << endl;
			}
		} else cout << "<p>Tidak ada Bentrok pada Jadwal</p>" << endl;
		
		cout << "<script src=\"drag.js\" type=\"text/javascript\"></script>" << endl;
	} 
	else {
		cout <<"<p style=\"font-family: Arial;\"><b>Fill up the form above and press solve<b></p>" <<endl;
	}
	cout<<"</body>"<<endl;
	cout<<"</html>"<<endl;
 
	return 0;
}
