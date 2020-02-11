#pragma once
#include "Repository.h"
#include "Observable.h"
#include "Contract.h"
#include "Validator.h"
#include "ActiuneUndo.h"
#include <memory>

using std::unique_ptr;
using std::make_unique;

class GRASPController: public Observable
{
private:
	Repository& repo;
	Validator& valid;
	Contract& contr;
	vector < unique_ptr<ActiuneUndo> > undoActions;

public:
	GRASPController(Repository&, Validator&, Contract&) noexcept;
	void add(string, int, string, string);
	const vector <Disciplina>& getAllElements() noexcept;
	vector <Disciplina> filterOre(int);
	vector <Disciplina> sorting(int);
	vector <Disciplina> filterCd(string);
	void deletee(string);
	bool search(string);
	void modify(string, int, string, string);
	void undo();

	int golContract();
	int addContract(string);
	vector < Disciplina >& getContract();
	int genContract(int);
	void saveContract(string);

	~GRASPController() {};
};

