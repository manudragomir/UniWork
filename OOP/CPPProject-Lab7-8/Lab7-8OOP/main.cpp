#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Contract.h"
#include "UI.h"
#include "GRASPController.h"
#include "Repository.h"
#include "Validator.h"
#include "Teste.h"
#include "RepoFile.h"

int main()
{
	TestAllExtins();
	{
	RepoFile repoF{ "disciplina.in" };


	Repository repo = Repository();
	Contract contr = Contract();
	Validator valid = Validator();
	GRASPController service = GRASPController(repoF, valid, contr);
	UI consola = UI(service);


	consola.run();
	}
	_CrtDumpMemoryLeaks();
}