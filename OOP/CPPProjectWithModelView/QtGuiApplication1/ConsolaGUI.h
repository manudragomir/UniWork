#pragma once
#include "GRASPController.h"
#include "Observer.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlistview.h>
#include "ModelList.h"

class ConsolaGUI : public QWidget, public Observer
{
private:
	GRASPController& service;
	QListWidget* lst;
	QListView* lstView = new QListView;
	MyListModel* model;

	QLineEdit* txtCadruDidactic;
	QLineEdit* txtMaterie;
	QLineEdit* txtNrOre;
	QLineEdit* txtTip;

	void initGUIComp();
	void initGUISemnals();
	void reloadList(const std::vector<Disciplina>&);
	//toate butoanele:
	QPushButton* btnAdauga;
	QPushButton* btnSterge = new QPushButton("Sterge");
	QPushButton* btnModifica = new QPushButton("Modifica");
	QPushButton* btnSortByDenumire = new QPushButton("Sort by denumire");
	QPushButton* btnSortByOre = new QPushButton("Sort by ore");
	QPushButton* btnSortByCd = new QPushButton("Sort by cadru");
	QPushButton* btnFilter = new QPushButton("Filter");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnCon = new QPushButton("Iete cosu");
	QPushButton* btnDesen = new QPushButton("Desen");
	QLineEdit* nrElemCos = new QLineEdit;
	QLabel* label = new QLabel("Numar elemente cos: ");

	//functiile
	void contract();
	void add();
	void sterge();
	void modify();
	void filter();
	void sort3();
	void sort1();
	void sort2();
	void undo();
	void desen();
	void update() override {
		nrElemCos->setText(QString::number(service.getContract().size()));
	}

public:
	ConsolaGUI(GRASPController& _service) : service{ _service } {
		initGUIComp();
		service.addObserver(this);
		model = new MyListModel(service.getAllElements());
		lstView->setModel(model);
		initGUISemnals();
		reloadList(service.getAllElements());
	};
};

