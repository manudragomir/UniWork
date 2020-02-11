#include "GRASPController.h"
#include <algorithm>

using std::sort;


GRASPController::GRASPController(Repository re, Validator v) : repo{ re }, valid{ v }{
}

void GRASPController::add(string den, int ore, string tip, string cd)
{
	Disciplina d{ den,ore,tip,cd };
	this->repo.storeRepo(d);
}

void GRASPController::deletee(string den)
{
	Disciplina d{ den,1,"a","a" };
	this->repo.deleteRepo(d);
}

bool GRASPController::search(string den)
{
	Disciplina d{ den,1,"a","a" };
	int pozitie = this->repo.searchRepo(d);

	if (pozitie == -1)
		return false;
	return true;

}

void GRASPController::modify(string den, int new_ora, string new_tip, string new_cd)
{
	Disciplina d{ den, new_ora, new_tip, new_cd };
	this->repo.updateRepo(d);
}

vector <Disciplina> GRASPController::filterOre(int nr_ore)
{
	vector < Disciplina > list = this->repo.getAllRepo();
	vector < Disciplina > final_list;
	for (auto disci : list)
	{
		if (disci.get_ore() >= nr_ore)
			final_list.push_back(disci);
	}
	return final_list;
}

vector <Disciplina> GRASPController::filterCd(string nume)
{
	vector < Disciplina > list = this->repo.getAllRepo();
	vector < Disciplina > final_list;
	for (auto disci : list)
	{
		if (disci.get_cadru_didactic() == nume)
			final_list.push_back(disci);
	}
	return final_list;
}

const vector<Disciplina>& GRASPController::getAllElements()
{
	return this->repo.getAllRepo();
}

bool cmpOre(const Disciplina& d1, const Disciplina& d2)
{
	return d1.get_ore() < d2.get_ore();
}

bool cmpDenumire(const Disciplina& d1, const Disciplina& d2)
{
	return d1.get_denumire() < d2.get_denumire();
}

bool cmpCd(const Disciplina& d1, const Disciplina& d2)
{
	if (d1.get_cadru_didactic() != d2.get_cadru_didactic())
		return d1.get_cadru_didactic() < d2.get_cadru_didactic();
	return d1.get_tip() < d2.get_tip();
}


vector<Disciplina> GRASPController::sorting(int cmd)
{
	vector < Disciplina > list = this->getAllElements();
	bool(*functionCMP)(const Disciplina& d1, const Disciplina& d2) {cmpOre};
	switch (cmd)
	{
		case 1:
			functionCMP = cmpOre;
			break;
		case 2:
			functionCMP = cmpDenumire;
			break;
		case 3:
			functionCMP = cmpCd;
			break;
	}

	for (int i = 0; i < list.size()-1; i++)
	{
		for (int j = i + 1; j < list.size(); j++)
		{
			if (functionCMP(list[i], list[j]) == false)
			{
				auto aux = list[i];
				list[i] = list[j];
				list[j] = aux;
			}
		}
	}
	return list;
}

GRASPController::~GRASPController()
{
}
