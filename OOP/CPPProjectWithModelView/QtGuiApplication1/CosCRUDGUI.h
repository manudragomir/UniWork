#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include "GRASPController.h"
#include <qtablewidget.h>
#include <qboxlayout.h>
#include <qinputdialog.h>

class ContractGUI : public QWidget, public Observer
{
private:
	GRASPController& serv;
	QPushButton* btnGoleste = new QPushButton("Goleste-l");
	QPushButton* btnGenereaza = new QPushButton("Genereaza sth");
	QTableWidget* tbl = new QTableWidget(1, 1);

	void InitConGUI() {
		//fac un tabel 

		QVBoxLayout* hb = new QVBoxLayout;
		this->setLayout(hb);

		QHBoxLayout* butons = new QHBoxLayout;
		QWidget* wid = new QWidget;
		wid->setLayout(butons);

		butons->addWidget(btnGenereaza);
		butons->addWidget(btnGoleste);

		hb->addWidget(wid);
		hb->addWidget(tbl);

	}

	void InitConSemnals() {
		QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
			//iau un nr;
			bool ok;
			int nr = QInputDialog::getInt(this, "Alegere", "Alege nr ore", 0, 0, 1000, 1, &ok);
			serv.genContract(nr);
			ReloadList(serv.getContract());
		});

		QObject::connect(btnGoleste, &QPushButton::clicked, [&]() {
			serv.golContract();
			ReloadList(serv.getContract());
		});
	}

	void ReloadList(vector <Disciplina>& v) {
		tbl->setColumnCount(1);
		tbl->setRowCount(v.size());

		int rowIndex = 0;
		for (const auto& d : v) {
			auto itemName = QString::fromStdString(d.get_denumire());
			QTableWidgetItem* item = new QTableWidgetItem(itemName);
			tbl->setItem(rowIndex, 0, item);
			++rowIndex;
		}
	}

public:
	ContractGUI(GRASPController& serv) : serv{ serv } {
		serv.addObserver(this);
		InitConGUI();
		InitConSemnals();
	};

	void update() override {
		ReloadList(serv.getContract());
	}
};