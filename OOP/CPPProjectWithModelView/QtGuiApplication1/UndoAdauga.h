#pragma once
#include "ActiuneUndo.h"
#include "Disciplina.h"
#include "Repository.h"

class UndoAdauga: public ActiuneUndo
{
	Disciplina disciplinaAdded;
	Repository& rep;
public:
	UndoAdauga(Repository& _rep, const Disciplina& d) : disciplinaAdded{ d }, rep{ _rep }{};
	void doUndo() override{
		rep.deleteRepo(disciplinaAdded);
	}
};

