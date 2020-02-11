#include "QtGuiApplication2.h"
#include <QtWidgets/QApplication>
#include "Teste.h"
#include "Repo.h"
#include "Ctrl.h"
#include "Valid.h"
#include "ConsGUI.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication2 w;
	Teste t;
	t.testAllExtins();
	
	Repo re{ "input.txt" };
	Valid vl;
	Ctrl ctrl{ re,vl };
	ConsGUI gui{ ctrl };
	gui.show();
	return a.exec();
}
