#include "RepoFile.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

void RepoFile::loadFromFile()
{
	ifstream fin(this->filename);
	Disciplina d;
	while (fin >> d)
	{
		this->storage.push_back(d);
	}
}

void RepoFile::storeToFile()
{
	ofstream fout(this->filename);
	for (auto it : this->storage)
		fout << it << "\n";
}
