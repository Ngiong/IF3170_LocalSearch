#include <bits/stdc++.h>
#include <map>
#include "getpost.h"
#include "Problem.hpp"
 
using namespace std;

#define COLOUR_CONST 4096
#define BENTROK_MAX 4096

typedef struct {
	string kodekuliah;
	int jammulai;
	int jamselesai;
	int idkuliah;
} Hasil;

typedef struct{
	string kodekuliah;
	string room;
	int jambentrok;
	int hari;
	int idkuliah;	
}Bentrok;
 
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
	cout << "Max Restart for Hill climbing (default : 100) : <input type = \"text\" name = \"step\"><br><br>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"SimulatedAnnealing\"> Simulated Annealing <br>" << endl;
	cout << "Temperature for Simulated Annealing (default : 1)                    : <input type = \"text\" name = \"temperature\"><br>" << endl;
	cout << "Descent Rate for Simulated Annealing (default : 0.004)               : <input type = \"text\" name = \"descentRate\"><br>" << endl;
	cout << "Maintain Temperature Attempts for Simulated Annealing (default : 35) : <input type = \"text\" name = \"maintainAttempts\"><br>" << endl;
	cout << "Maximum Iteration for Simulated Annealing (default : 2600)           : <input type = \"text\" name = \"maxIter\"><br><br>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"GeneticAlgorithm\"> Genetic Algorithm <br><br>" << endl;
	cout << "<p>Browse File: <input type=\"file\" name=\"userfile\" /></p>"<<endl;
	cout<<"<input type=\"submit\" value=\"Solve\" style=\"background-color: #0080ff;border: none;color: white;padding: 10px 27px;text-align: center;text-decoration: none;display: inline-block;font-size: 14px;margin: 4px 2px;cursor: pointer;\" />"<<endl;
	cout<<"</form>"<<endl;

 	if(Get.find("algo")==Get.end() || Get.find("userfile")==Get.end()){
		cout <<"<p style=\"font-family: Arial;\"><b>Fill up the form above and press solve<b></p>" <<endl;
	} 
	else {
		string file = Get["userfile"];
		file = "../tc/" + file;
		Problem n(file);
		if(Get["algo"] == "HillClimbing"){
			if (Get["step"] != "") {
				n.solveUsingHill(stoi(Get["step"]));
			}
			else {
				n.solveUsingHill(100);
			}
		} 
		else if(Get["algo"] == "SimulatedAnnealing"){
			// n.solveUsingSA(1, 0.01, 10, 120);
			// n.solveUsingSA(10, 0.004, 35, 2600);
			if (Get["temperature"] == "" || Get["descentRate"] == "" || Get["maintainAttempts"] == "" || Get["maxIter"] == "") {
				n.solveUsingSA(1, 0.004, 35, 2600);
			}
			else {
				n.solveUsingSA(stof(Get["temperature"]), stof(Get["descentRate"]), stoi(Get["maintainAttempts"]), stoi(Get["maxIter"]));
			}	
		} 
		else {
			n.solveUsingGA(64, 100);	
		} 
		
		cout << "<br>" << endl;
		cout << "<h2 class=\"schedule\">Result</h2>" << endl;
		cout << "<br><br>" << endl;
		int T = n.getNRoom();
		
		// ini buat nampung bentrok nya
		Bentrok arrBentrok[BENTROK_MAX];
		int bentrokIterator = 0;
		
		map<string,int> mapRoomName;
		 
		for(int i = 0; i < T; i++) {
			string RoomName = n.getRuang(i).getName();	
			
			if(mapRoomName.count(RoomName)!=0) {
				// do nothing
			}
			else {
				mapRoomName[RoomName] = 1;		
				cout << "<h3 class=\"schedule\">" << RoomName << "</h3>" << endl;
				Hasil temp[12][6];
				int countFill = 0;
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
							
						if(temp[n.getKuliah(j).getCurrentStartTime()-6][k].kodekuliah == "-"){
							// check duration
							temp[n.getKuliah(j).getCurrentStartTime()-6][k].kodekuliah = n.getKuliah(j).getKode();
							if(n.getKuliah(j).getDuration() > 1) {
								int duration = n.getKuliah(j).getDuration();
								duration -= 1;
								for(int a = n.getKuliah(j).getCurrentStartTime()-6; a <= n.getKuliah(j).getCurrentStartTime()-6 + duration; a++){
									if(temp[a][k].kodekuliah == "-" || temp[a][k].kodekuliah == n.getKuliah(j).getKode()){
										temp[a][k].kodekuliah = n.getKuliah(j).getKode();
										temp[a][k].idkuliah = j+1;
										countFill += 1;
									} else {
										arrBentrok[bentrokIterator].kodekuliah = n.getKuliah(j).getKode();
										arrBentrok[bentrokIterator].hari = k;
										arrBentrok[bentrokIterator].jambentrok = a;
										arrBentrok[bentrokIterator].idkuliah = j+1;
										arrBentrok[bentrokIterator].room = RoomName;
										bentrokIterator++;
									}
								}
							}
							else
							{
								temp[n.getKuliah(j).getCurrentStartTime()-6][k].idkuliah = j+1;
								countFill += 1;
							}
						}
						else {
							int Bentrokduration = n.getKuliah(j).getDuration();
							if(Bentrokduration > 1){
								Bentrokduration -= 1;
								for(int a = n.getKuliah(j).getCurrentStartTime()-6; a <= n.getKuliah(j).getCurrentStartTime()-6 + Bentrokduration; a++){
									if(temp[a][k].kodekuliah != "-" && temp[a][k].kodekuliah != n.getKuliah(j).getKode()){	
										arrBentrok[bentrokIterator].kodekuliah = n.getKuliah(j).getKode();
										arrBentrok[bentrokIterator].hari = k;
										arrBentrok[bentrokIterator].jambentrok = a;
										arrBentrok[bentrokIterator].idkuliah = j+1;
										arrBentrok[bentrokIterator].room = RoomName;
										bentrokIterator++;
									} else {
										temp[a][k].kodekuliah = n.getKuliah(j).getKode();
										countFill += 1;
										temp[a][k].idkuliah = j+1; 
									}
								}
							}
							else {
								arrBentrok[bentrokIterator].kodekuliah = n.getKuliah(j).getKode();
								arrBentrok[bentrokIterator].hari = k;
								arrBentrok[bentrokIterator].jambentrok = n.getKuliah(j).getCurrentStartTime()-6;
								arrBentrok[bentrokIterator].idkuliah = j+1;
								arrBentrok[bentrokIterator].room = RoomName;
								bentrokIterator++;
							}
						}
					}
				}
				
				// nge cout disini 
				for(int b = 0; b < 12; b++){
					if(b == 0){
						for(int c = 0; c < 6; c++){
							int colour = (temp[b][c].idkuliah)*COLOUR_CONST;
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
							int colour = (temp[b][c].idkuliah)*COLOUR_CONST;
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
				cout << "<br>" << endl;
				cout << "<p><b>Persen keefektifan ruangan ini (" << countFill << "/" << n.getAvailableDuration(RoomName) << ") =" << (float)((countFill * 100)) / n.getAvailableDuration(RoomName) << "%</b></p>" << endl;
				cout << "<br>" << endl;
			}
		}
			// buat bentrok
		cout << "<h3 class=\"schedule\">Bentrok</h3>" << endl;
		cout << "Jumlah Bentrok " << n.countConflictCourses() << endl;
		cout << "<br></br>" << endl;
		cout << "Jumlah matkul masuk ke jadwal tapi tidak terlihat (keterbatasan GUI) :  " << bentrokIterator << endl;
		cout << "<br>" << endl;
		if(bentrokIterator >= 1){
			for(int d = 0; d < bentrokIterator; d++){
				int colour = arrBentrok[d].idkuliah*COLOUR_CONST;
				cout << "<div class=\"column\" draggable=\"true\"><header style=\"background-color:" << colour << "\">"<<arrBentrok[d].kodekuliah<<"</header></div>" << endl;
				if(d % 6 == 5 || d == bentrokIterator-1)
					cout << "<br><br>" << endl;
			}
			
			cout << "<br><br>" << endl;
			cout << "<h3 class=\"schedule\">Detail Bentrok</h3>" << endl;
			cout << "<h4>Berikut detail bentrok dari hasil solver : </h4>" << endl;
			cout << "<div style=\"border: 5px solid red;border-radius: 3px;text-align: center;\">" << endl;
			for(int d = 0; d < bentrokIterator; d++){
				int colour = arrBentrok[d].idkuliah*COLOUR_CONST;
				cout <<"<b style=\"color:white; background-color:" << colour << "\">"<< arrBentrok[d].kodekuliah << "</b> pada ruang " <<"<b>"<< arrBentrok[d].room << "</b> di hari ke- " <<"<b>"<<arrBentrok[d].hari << "</b> pada jam : "<<"<b>"<<arrBentrok[d].jambentrok <<"</b>"<<endl;
				cout << "<br>" << endl;
			}
			cout << "</div>" << endl;
		} 
		else cout << "<p>Tidak ada Bentrok pada Jadwal</p>" << endl;
		
		cout << "<script src=\"drag.js\" type=\"text/javascript\"></script>" << endl;

	} 
	cout<<"</body>"<<endl;
	cout<<"</html>"<<endl;
 
	return 0;
}
