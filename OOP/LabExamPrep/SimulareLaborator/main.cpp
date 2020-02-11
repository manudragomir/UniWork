#include "SimulareLaborator.h"
#include <QtWidgets/QApplication>
#include "Repo.h"
#include "GRASP.h"
#include "ConsolaGUI.h"
#include "Teste.h"
#include "ConsolaGUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimulareLaborator w;
	Teste t;
	t.testAllExtins();
	Repo re{ "echipe.txt" };
	GRASP serv{ re };
	ConsolaGUI gui{ serv };
	gui.show();
	return a.exec();
}
