#include "Repository.h"
#include "Excep.h"


Repository::Repository()
{
	
}

void Repository::storeRepo(const Disciplina& d)
{
	/*if (searchRepo(d) != -1)
		throw RepoExc("Nu se poate face add cu un element deja existent");
		
	this->storage.push_back(d);*/
	auto it = std::find(this->storage.begin(), this->storage.end(), d);
	if (it != this->storage.end())
	{
		throw RepoExc("Nu se poate face add cu un element deja existent\n");
	}
	
	this->storage.push_back(d);

}

Disciplina Repository::getElement(const Disciplina& d)
{
	auto it = std::find(this->storage.begin(), this->storage.end(), d);
	if (it == this->storage.end())
	{
		return d;
	}

	return *it;
}

void Repository::deleteRepo(const Disciplina& d)
{
	/*const int pozitie = searchRepo(d);
	if (pozitie == -1)
		throw RepoExc("Nu se poate sterge un element inexistent");
	
	//this->storage.erase(this->storage.begin() + pozitie);
	this->storage.erase(pozitie);*/
	auto it = std::find(this->storage.begin(), this->storage.end(), d);
	if (it == this->storage.end())
	{
		throw RepoExc("Nu se poate sterge un element inexistent\n");
	}

	this->storage.erase(it);
}

bool Repository::searchRepo(const Disciplina& d)
{
	auto it = std::find(this->storage.begin(), this->storage.end(), d);

	if (it == this->storage.end())
		return false;
	return true;
}

void Repository::updateRepo(const Disciplina& d)
{
	auto it = std::find(this->storage.begin(), this->storage.end(), d);
	if (it == this->storage.end())
	{
		throw RepoExc("Nu se poate updata un element inexistent\n");
	}
		
	*it = d;
}

const vector <Disciplina>& Repository::getAllRepo() noexcept
{
	return this->storage;
}


Repository::~Repository()
{
}
