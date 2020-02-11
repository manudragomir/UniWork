/*#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>*/

#include "Contract.h"
#include "GRASPController.h"
#include "Repository.h"
#include "Validator.h"
#include "Teste.h"
#include "RepoFile.h"

#include "ConsolaGUI.h"
#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

	TestAllExtins();
	QApplication a(argc, argv);
	
	RepoFile repoF{ "disciplina.in" };


	Repository repo;
	Contract contr;
	Validator valid;
	GRASPController service{ repoF, valid, contr };
	//UI consola = UI(service);
	ConsolaGUI cons{ service };
	cons.show();
	a.setStyle("fusion");
	a.exec();
	return 0;
}
