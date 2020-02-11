#include "Repository.h"
#include "Excep.h"


Repository::Repository()
{
	
}

void Repository::storeRepo(const Disciplina& d)
{
	if (searchRepo(d) != -1)
		throw RepoExc("Nu se poate face add cu un element deja existent");
		
	this->storage.push_back(d);
}

void Repository::deleteRepo(const Disciplina& d)
{
	const int pozitie = searchRepo(d);
	if (pozitie == -1)
		throw RepoExc("Nu se poate sterge un element inexistent");
	
	//this->storage.erase(this->storage.begin() + pozitie);
	this->storage.erase(pozitie);
}

int Repository::searchRepo(const Disciplina& d)
{
	int i = 0;
	for (const auto& disci : this->storage)
	{
		if (d.egal(disci) == true)
			return i;
		i++;
	}

	return -1;
}

void Repository::updateRepo(const Disciplina& d)
{
	const int pozitie = searchRepo(d);
	if (pozitie == -1)
		throw RepoExc("Nu se poate face update pentru un element inexistent!");
		
		
	this->storage[pozitie] = d;
	
}

const vector <Disciplina>& Repository::getAllRepo()
{
	return this->storage;
}


Repository::~Repository()
{
}
