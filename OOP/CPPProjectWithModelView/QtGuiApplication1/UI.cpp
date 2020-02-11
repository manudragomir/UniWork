#include "UI.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

UI::UI(GRASPController& serv) : service{ serv } {};

void UI::UI_add()
{
	string den{ " " }, tip{ " " }, cd{ " " }, nr{ " " };
	cout << "Denumire: "; cin >> den;
	cout << "Numar ore: "; cin >> nr;
	cout << "Tip: "; cin >> tip;
	cout << "Cadru didactic: "; cin >> cd;
	const int _nr = std::stoi(nr);
	this->service.add(den, _nr, tip, cd);
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
	const bool is_in = this->service.search(den);
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
	string new_ore{ " " };
	string new_tip{ " " }, new_cd{ " " };	
	cout << "Denumirea veche: "; cin >> den;
	cout << "Numar ore(nou): "; cin >> new_ore;
	cout << "Tip(nou): "; cin >> new_tip;
	cout << "Cadru didactic(nou): "; cin >> new_cd;
	const int _new_ore = stoi(new_ore);
	this->service.modify(den, _new_ore, new_tip, new_cd);
	cout << "Modificarea s-a efectuat cu succes\n";
}

void UI::UI_filter()
{
	string _cmd{ " " };
	vector < Disciplina > list;
	cout << "0-nr de ore\n1-cadru didactic\n";
	cin >> _cmd;
	const int cmd = stoi(_cmd);
	if (cmd == 0)
	{
		string _nr_ore{ " " };
		cout << "Sa fie mai multe de: "; cin >> _nr_ore;

		const int nr_ore = stoi(_nr_ore);
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

void UI::UI_undo()
{
	this->service.undo();
}

void UI::UI_golContract()
{
	printf("%d\n", this->service.golContract());
}

void UI::UI_addContract()
{
	string str;
	cout << "Nume disciplina: ";
	cin >> str;
	printf("%d\n", this->service.addContract(str));
}

void UI::UI_genContract()
{
	int nr;
	cout << "Nr de materii: ";
	cin >> nr;
	printf("%d\n", this->service.genContract(nr));
}

void UI::UI_saveContract()
{
	this->service.saveContract("contract.txt");
}

void UI::UI_getContract()
{
	auto contr = this->service.getContract();
	for (auto it : contr)
	{
		cout << it << "\n";
	}
}

void UI::populeaza()
{
	this->service.add("OOP", 10, "S2", "Istvan");
	this->service.add("FP", 10, "S1", "Istvan");
	this->service.add("SO", 5, "S2", "Boian");
	this->service.add("SD", 10, "S2", "Serban");
	this->service.add("SDA", 10, "S2", "Didi");
	this->service.add("ALGEBRA", 7, "S1", "Mo2");
}

void UI::run()
{
	while(1)
	{
		cout << this->comenzi;
		string _cmd{ " " };
		cout << "Introdu comanda: ";
		cin >> _cmd;

		const int cmd = stoi(_cmd);
		try {

			switch (cmd)
			{
			case -1:
				populeaza();
				break;
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
			case 8:
				UI_golContract();
				break;
			case 9:
				UI_addContract();
				break;
			case 10:
				UI_genContract();
				break;
			case 11:
				UI_saveContract();
				break;
			case 12:
				UI_getContract();
				break;
			case 13:
				UI_undo();
				break;
			default:
				cout << "Comanda nu exista!\n";

			}
		}
		catch (RepoExc& re)
		{
			cout << re << "\n";
		}

		catch (DisciplinaExc& de)
		{
			cout << de << "\n";
		}

		catch (std::invalid_argument& )
		{
			cout << "date invalide\n";
		}
	}
	
}

UI::~UI()
{
}
