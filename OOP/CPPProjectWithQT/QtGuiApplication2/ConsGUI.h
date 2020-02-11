#pragma once
#include <qwidget.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "BackWindow.h"
#include "Ctrl.h"
class ConsGUI : public QWidget, public Observer
{
private:
	Ctrl& ctrl;
	void initGUIComp();
	void initSemnals();
	void reloadList(const vector <Task>& v);
	QTableWidget* tbl = new QTableWidget;
	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtDesc = new QLineEdit;
	QLineEdit* txtStare = new QLineEdit;
	QLineEdit* txtProgr = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{ "Adauga" };
	QLineEdit* filtr = new QLineEdit;
public:
	ConsGUI(Ctrl& ctrl) : ctrl{ ctrl } {
		ctrl.addObserver(this);
		initGUIComp();
		initSemnals();
		reloadList(ctrl.getAll());
		BackWindow* b1 = new BackWindow{ "open", ctrl };
		BackWindow* b2 = new BackWindow{ "closed", ctrl };
		BackWindow* b3 = new BackWindow{ "inprogress",ctrl };
		b1->show();
		b2->show();
		b3->show();
	};
	void update() override {
		reloadList(ctrl.getAll());
	}
	~ConsGUI() {};
};

