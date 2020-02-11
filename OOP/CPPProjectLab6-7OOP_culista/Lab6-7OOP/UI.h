#pragma once
#include "GRASPController.h"
#include <string>

using std::string;

class UI
{
private:
	GRASPController service;
	string comenzi = "1-Adauga\n2-Sterge\n3-Modifica\n4-Afisare\n5-Cautare\n6-Filtrare\n7-Sortare\n0-Exit\n";

public:
	UI() = delete;
	UI(GRASPController serv);
	void UI_add();
	void UI_delete();
	void UI_print();
	void UI_search();
	void UI_modify();
	void UI_filter();
	void UI_sort();
	void run();
	~UI();
};

