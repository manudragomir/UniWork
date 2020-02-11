#include "UI.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

UI::UI(GRASPController serv): service{serv} {
}

void UI::UI_add()
{
	string den{ " " }, tip{ " " }, cd{ " " };
	int nr{ 0 };
	cout << "Denumire: "; cin >> den;
	cout << "Numar ore: "; cin >> nr;
	cout << "Tip: "; cin >> tip;
	cout << "Cadru didactic: "; cin >> cd;
	this->service.add(den, nr, tip, cd);
	cout << "Adaugarea a avut loc cu succes!\n";
}

void UI::UI_delete()
{
	string den{ " " };
	cout << "Materia de sters: "; cin >> den;
	this->service.deletee(den);
	cout << "Elementul a fost sters cu succes\n";
}

void UI::UI_search()
{
	string den{ " " };
	cout << "Materia de cautat: "; cin >> den;
	bool is_in = this->service.search(den);
	if (is_in == false)
	{
		cout << "Nu s-a gasit in repository!\n";
	}

	else
	{
		cout << "Elementul cautat exista\n";
	}
}

void UI::UI_modify()
{
	string den{ " " };
	int new_ore{ 0 };
	string new_tip{ " " }, new_cd{ " " };	
	cout << "Denumirea veche: "; cin >> den;
	cout << "Numar ore(nou): "; cin >> new_ore;
	cout << "Tip(nou): "; cin >> new_tip;
	cout << "Cadru didactic(nou): "; cin >> new_cd;
	this->service.modify(den, new_ore, new_tip, new_cd);
	cout << "Modificarea s-a efectuat cu succes\n";
}

void UI::UI_filter()
{
	int cmd{ 0 };
	vector < Disciplina > list;
	cout << "0-nr de ore\n1-cadru didactic\n";
	cin >> cmd;
	if (cmd == 0)
	{
		int nr_ore{ 0 };
		cout << "Sa fie mai multe de: "; cin >> nr_ore;
		list = this->service.filterOre(nr_ore);
	}

	else
	{
		string nume{ " " };
		cout << "Prof: "; cin >> nume;
		list = this->service.filterCd(nume);
	}

	for (auto el : list)
	{
		cout << el.toString() << "\n";
	}
}

void UI::UI_sort()
{
	int cmd{ 0 };
	cout << "Sortare dupa: 1-Numar ore\n2-Denumire\n3-Cadru Didactic + Tip\n"; cin >> cmd;
	vector < Disciplina> list = this->service.sorting(cmd);
	for (const auto& el : list)
		cout << el.toString() << "\n";

}

void UI::UI_print()
{
	const vector < Disciplina >& list = this->service.getAllElements();
	for (const auto& disci : list)
		cout << disci.toString() << "\n";
}

void UI::run()
{
	while(1)
	{
		cout << this->comenzi;
		int cmd{ 0 };
		cout << "Introdu comanda: ";
		cin >> cmd;
		try {

			switch (cmd)
			{
			case 0:
				//Exit
				return;
			case 1:
				UI_add();
				break;
			case 2:
				UI_delete();
				break;
			case 3:
				UI_modify();
				break;
			case 4:
				UI_print();
				break;
			case 5:
				UI_search();
				break;
			case 6:
				UI_filter();
				break;
			case 7:
				UI_sort();
				break;
			default:
				cout << "Comanda nu exista!\n";

			}
		}
		catch (RepoExc& re)
		{
			cout << re.toString() << "\n";
		}

		catch (DisciplinaExc& de)
		{
			cout << de.toString() << "\n";
		}
	}
	
}

UI::~UI()
{
}
