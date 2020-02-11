#pragma once
#include "Repo.h"
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>

using std::string;
using std::vector;
using std::pair;

class GRASP
{
private:
	Repo& re;
public:
	GRASP(Repo& _re) : re{ _re } {};
	vector <Echipa>& getAllRepo() {
		return re.getAll();
	}
	vector <Echipa> getSpania() {
		//returneaza toate echipele care au ca tara de origine Spania
		vector < Echipa > spList;
		auto list = re.getAll();
		for (auto it : list) {
			if (it.getTara() == "Spania")
				spList.push_back(it);
		}
		return spList;
	}
	vector <Echipa> getAnglia() {
		//returneaza toate echipele care au ca tara de origine Anglia
		vector < Echipa > anList;
		auto list = re.getAll();
		for (auto it : list) {
			if (it.getTara() == "Anglia")
				anList.push_back(it);
		}
		return anList;
	}
	string getMaxAtac();
	string getMaxMij();
	string getMaxAp();
	vector < string > rezolvaCampionat();

	pair < int, int > solveMeci(Echipa& e1, Echipa& e2) {
		//in: doua echipe;
		//return: pereche ce are scorul dintre echipe
		pair < int, int > scor;
		auto rating1 = (e1.getAp() + e1.getMij() + e1.getAtac()) / 3;
		auto rating2 = (e2.getAp() + e2.getMij() + e2.getAtac()) / 3;
		if (rating1 == rating2) {
			scor.first = scor.second = rand() % 6;
		}
		else if (rating1 > rating2) {
			scor.second = rand() % 2;
			scor.first = scor.second + rand() % 3 + 1;
		}
		else {
			scor.first = rand() % 2;
			scor.second = scor.first + rand() % 3 + 1;
		}
		return scor;
	}
	~GRASP() {};
};

