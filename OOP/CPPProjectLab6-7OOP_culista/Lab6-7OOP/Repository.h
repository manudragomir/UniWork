#pragma once

#include "Disciplina.h"
#include "vector.h"

class Repository
{
private:
	vector < Disciplina > storage;

public:
	Repository();
	void storeRepo(const Disciplina&);
	void deleteRepo(const Disciplina&);
	void updateRepo(const Disciplina&);
	int searchRepo(const Disciplina&);
	const vector<Disciplina>& getAllRepo();
	~Repository();
};

