#include "Repo.h"
#include "Echipa.h"
#include <fstream>

using std::ifstream;

void Repo::loadFromFile()
{
	//desc: citeste datele din fisier, entitati de tip Echipa
	list.clear();
	ifstream fin(filename);
	Echipa aux;
	while (!fin.eof()) {
		fin >> aux;
		list.push_back(aux);
	}
}
