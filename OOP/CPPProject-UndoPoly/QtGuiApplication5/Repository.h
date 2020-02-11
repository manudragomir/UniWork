#pragma once

#include "Disciplina.h"
#include <vector>

using std::vector;


class Repository
{
	friend class GRASPController;
protected:
	vector < Disciplina > storage;
	
public:
	Repository();
	Disciplina getElement(const Disciplina &);
	virtual void storeRepo(const Disciplina&);
	virtual void deleteRepo(const Disciplina&);
	virtual void updateRepo(const Disciplina&);
	bool searchRepo(const Disciplina&);
	const vector<Disciplina>& getAllRepo() noexcept;
	~Repository();
};

