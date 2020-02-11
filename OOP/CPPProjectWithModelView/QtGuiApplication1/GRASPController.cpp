#include "GRASPController.h"
#include "UndoAdauga.h"
#include "UndoSterge.h"
#include "UndoUpdate.h"
#include <algorithm>
#include <random>

using std::sort;


GRASPController::GRASPController(Repository& re, Validator& v, Contract& c) noexcept : repo{ re }, valid{ v }, contr{ c } {};

void GRASPController::add(string den, int ore, string tip, string cd)
{
	Disciplina d{ den,ore,tip,cd };
	this->repo.storeRepo(d);
	undoActions.push_back(std::move (make_unique<UndoAdauga>(this->repo,d)));
}

void GRASPController::deletee(string den)
{
	Disciplina d{ den,1,"a","a" };

	Disciplina d1 = this->repo.getElement(d);

	this->repo.deleteRepo(d);	
	
	notify();
	undoActions.push_back(std::move(make_unique<UndoSterge>(this->repo, d1)));

}

bool GRASPController::search(string den)
{
	Disciplina d{ den,1,"a","a" };
	return this->repo.searchRepo(d);

}

void GRASPController::modify(string den, int new_ora, string new_tip, string new_cd)
{
	Disciplina d{ den, new_ora, new_tip, new_cd };
	Disciplina d1 = this->repo.getElement(d);
	this->repo.updateRepo(d);
	notify();
	undoActions.push_back(std::move(make_unique<UndoUpdate>(this->repo, d1)));
}

vector <Disciplina> GRASPController::filterOre(int nr_ore)
{
	vector < Disciplina > list = this->repo.getAllRepo();
	vector < Disciplina > final_list;
	/*for (auto disci : list)
	{
		if (disci.get_ore() >= nr_ore)
			final_list.push_back(disci);
	}
	return final_list;*/
	auto it = copy_if(list.begin(), list.end(), std::back_inserter(final_list), [nr_ore](Disciplina& d) noexcept {return d.get_ore() >= nr_ore; });
	return final_list;
}

vector <Disciplina> GRASPController::filterCd(string nume)
{
	vector < Disciplina > list = this->repo.getAllRepo();
	vector < Disciplina > final_list;
	/*for (auto disci : list)
	{
		if (disci.get_cadru_didactic() == nume)
			final_list.push_back(disci);
	}
	return final_list;*/
	auto it = copy_if(list.begin(), list.end(), std::back_inserter(final_list), [&nume](Disciplina& d)noexcept {return (d.get_cadru_didactic() == nume); });
	return final_list;
}

const vector<Disciplina>& GRASPController::getAllElements() noexcept
{
	return this->repo.getAllRepo();
}

/*
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
*/


vector<Disciplina> GRASPController::sorting(int cmd)
{
	vector < Disciplina > list = this->getAllElements();
	/*
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
	*/
	if (cmd == 1)
	{
		auto sortRuleLambda = [](const Disciplina& s1, const Disciplina& s2)noexcept
		{
			return s1.get_ore() < s2.get_ore();
		};
		sort(list.begin(), list.end(), sortRuleLambda);
	}

	else if (cmd == 2)
	{
		auto sortRuleLambda = [](const Disciplina& s1, const Disciplina& s2)noexcept
		{
			return s1.get_denumire() < s2.get_denumire();
		};
		sort(list.begin(), list.end(), sortRuleLambda);
	}

	else
	{
		auto sortRuleLambda = [](const Disciplina& s1, const Disciplina& s2)noexcept
		{
			if (s1.get_cadru_didactic() == s2.get_cadru_didactic())
				return s1.get_tip() < s2.get_tip();

			return s1.get_cadru_didactic() < s2.get_cadru_didactic();
		};
		sort(list.begin(), list.end(), sortRuleLambda);
	}


	return list;
}

void GRASPController::undo()
{
	if (undoActions.empty())
	{
		throw DisciplinaExc{ "Nu se mai poate da undo" };
	}

	auto act = undoActions.back().get();
	act->doUndo();
	undoActions.pop_back();
}

int GRASPController::golContract()
{
	this->contr.goleste();
	notify();
	return this->contr.get().size();
}

int GRASPController::addContract(string s)
{
	auto disci = this->repo.getElement(Disciplina(s, -1, "", ""));
	if(disci.get_ore()!=-1)
		this->contr.add(disci);
	notify();
	return this->contr.get().size();
}

vector<Disciplina>& GRASPController::getContract()
{
	for (const auto& disci : this->contr.get()) {
		if (search(disci.get_denumire()) == false)
			this->contr.sterge(disci);
	}

	return this->contr.get();
}

int GRASPController::genContract(int nr)
{
	auto v = this->repo.getAllRepo();
	this->contr.goleste();
	for (int i = 0; i < nr; i++)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> dist(0, v.size() - 1);
		int rndNr = dist(mt);// numar aleator intre [0,size-1]
		this->contr.add(v[rndNr]);
	}
	notify();
	return this->contr.get().size();
}

void GRASPController::saveContract(string file)
{
	this->contr.store(file);
}
