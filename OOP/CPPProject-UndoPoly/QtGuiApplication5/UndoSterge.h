#pragma once
#include "Repository.h"
#include "ActiuneUndo.h"

class UndoSterge :public ActiuneUndo
{
private:
	Repository& re;
	Disciplina d;
public:
	UndoSterge(Repository& _re, const Disciplina& _d) : re{ _re }, d{ _d }{};
	void doUndo() override {
		re.storeRepo(d);
	}
};

