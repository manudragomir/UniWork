#pragma once
#include "GRASPController.h"
#include "UI.h"
#include <string>

using std::string;

class UI
{
private:
	GRASPController& service;
	string comenzi = "1-Adauga\n2-Sterge\n3-Modifica\n4-Afisare\n5-Cautare\n6-Filtrare\n7-Sortare\n8-Goleste contract\n9-Adauga in contract\n10-Genereaza contract\n11-Salveaza contract in fisier\n12-Print contract\n13-Undo\n0-Exit\n";
	void populeaza();
public:
	UI() = delete;
	UI(GRASPController&);
	void UI_add();
	void UI_delete();
	void UI_print();
	void UI_search();
	void UI_modify();
	void UI_filter();
	void UI_sort();
	void UI_undo();
	void UI_golContract();
	void UI_addContract();
	void UI_genContract();
	void UI_saveContract();
	void UI_getContract();
	void run();
	~UI();
};

