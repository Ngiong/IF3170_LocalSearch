#include <bits/stdc++.h>
#include "Problem.hpp"
using namespace std;

int main() {
	//Problem n;
	string file;
	
	cout << "********************" << endl;
	cout << "*** LOCAL SEARCH ***" << endl;
	cout << "********************" << endl << endl;
	cout << "Masukkan testcase: "; cin >> file;
	file = "../tc/" + file;
	//n.fileToVar(file);
	Problem n(file);

	cout << "yolo"  << endl;
	//n.solveUsingSA(1, 0.01, 10, 100);
	n.solveUsingHill(10);
	int count = n.countConflictCourses();
	cout << "CONFLICT : " << count << endl;
	
	////////////////////////////////////////////////////
	//////////// Bagian GUI ////////////////////////////
	////////////////////////////////////////////////////
	//* kalo mw ngetes, pindahin semua filenya ke xampp/htdocs terus compile : g++ MainDriver.cpp -o MainDriver.cgi -std=c++11
	//* ati2 kalo cout di terminal, kode dibawah ini di comment dulu jng lupa wkwk
	/*
	cout<<"Content-type: text/html"<<endl<<endl;
	cout <<"<html>"<<endl;
	cout << "<head>" << endl;
	cout << "<title>Course Scheduling</title>" << endl;
	cout << "<link href=\"drag.css\" rel=\"stylesheet\" /> " << endl;
	cout << "</head>" << endl;
	
	cout << "<body>" << endl;
	cout << "<p><H1>COURSE SCHEDULING AI</H1></p>" << endl;
	cout << "<p>Select the Algorithm : </p>" << endl;
	cout << "<forms>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"HillClimbing\"> Hill Climbing <br>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"SimulatedAnnealing\"> Simulated Annealing <br>" << endl;
	cout << "<input type = \"radio\" name = \"algo\" value = \"GeneticAlgorithm\"> Genetic Algorithm <br><br>" << endl;
	cout << "<input type = \"submit\" name = \"submit\" value = \"Solve\" >" << endl;
	cout << "</forms>" << endl;
	
	cout << "<br><br><br>" << endl;
	cout << "<h2 class=\"schedule\">Schedule Table</h2>" << endl;
	cout << "<div id = \"columns\"> " << endl;
	cout << "<h2><pre>       Senin              Selasa              Rabu               Kamis               Jumat</pre></h2>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>A</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>B</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>C</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>D</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>E</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>F</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>G</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>H</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>I</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>J</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>K</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>L</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>M</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>N</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>O</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>P</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>Q</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>R</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>S</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>T</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>U</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>V</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>W</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>X</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>Y</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>Z</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AA</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AB</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AC</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AD</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AE</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AF</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AG</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AH</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AI</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AJ</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AK</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AL</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AM</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AN</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AO</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AP</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AQ</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AR</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AS</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AT</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AU</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AV</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AW</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AX</header></div><br><br><br>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AY</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>AZ</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>BA</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>BB</header></div>" << endl;
	cout << "<div class=\"column\" draggable=\"true\"><header>BC</header></div><br><br><br>" << endl;
	cout << "<div>" << endl;
	cout << "<script src=\"drag.js\" type=\"text/javascript\"></script>" << endl;
	cout << "</body>" << endl;
	cout << "</html>" << endl;
	*/
	return 0;
}

