#pragma once
#include "GRASP.h"
#include "qwidget.h"
#include "qlistwidget.h"
#include "qtablewidget.h"
#include "qpushbutton.h"

class ConsolaGUI: public QWidget
{
private:
	GRASP& serv;
	QListWidget* lstAnglia;
	QListWidget* lstSpania;
	QTableWidget* rezultate;
	QPushButton* btnGenereaza;
	void initGUIComp();
	void initGUISemnals();
	void reloadLists(vector<Echipa>& lista);
public:
	ConsolaGUI(GRASP& _serv) : serv{ _serv } {
		initGUIComp();
		initGUISemnals();
		reloadLists(serv.getAllRepo());
	};
	~ConsolaGUI() {};
};

