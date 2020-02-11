#pragma once
#include "Repository.h"
#include "ActiuneUndo.h"

class UndoUpdate :public ActiuneUndo
{
private:
	Repository& re;
	Disciplina d;
public:
	UndoUpdate(Repository& _re, const Disciplina& _d) : re{ _re }, d{ _d }{};
	void doUndo() override {
		re.updateRepo(d);
	}
};

