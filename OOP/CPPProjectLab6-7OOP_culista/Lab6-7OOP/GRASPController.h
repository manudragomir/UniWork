#pragma once
#include "Repository.h"
#include "Validator.h"

class GRASPController
{
private:
	Repository repo;
	Validator valid;

public:
	GRASPController(Repository, Validator);
	void add(string, int, string, string);
	const vector <Disciplina>& getAllElements();
	vector <Disciplina> filterOre(int);
	vector <Disciplina> sorting(int);
	vector <Disciplina> filterCd(string);
	void deletee(string);
	bool search(string);
	void modify(string, int, string, string);
	

	~GRASPController();
};

