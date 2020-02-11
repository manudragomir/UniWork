#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "UI.h"
#include "GRASPController.h"
#include "Repository.h"
#include "Validator.h"
#include "Teste.h"

int main()
{
	TestAllExtins();
	_CrtDumpMemoryLeaks();

	Repository repo = Repository();
	Validator valid = Validator();
	GRASPController service = GRASPController(repo, valid);
	UI consola = UI(service);
	
	consola.run();
}