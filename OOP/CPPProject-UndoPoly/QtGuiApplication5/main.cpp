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
#include "ConsolaGUI.h"

#include "QtGuiApplication5.h"
#include <QtWidgets/QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
	{
		QApplication a(argc, argv);
		//PetRepo rep;
		RepoFile repoF{ "disciplina.in" };


		Repository repo = Repository();
		Contract contr = Contract();
		Validator valid = Validator();
		GRASPController service = GRASPController(repoF, valid, contr);
		//UI consola = UI(service);

		ConsolaGUI gui{ service };
		gui.show();
		a.exec();
	}

	return 0;
}
