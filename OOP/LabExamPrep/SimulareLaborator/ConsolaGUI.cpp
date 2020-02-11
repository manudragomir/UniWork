#include "ConsolaGUI.h"
#include <qboxlayout.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <algorithm>
#include <ctime>


void ConsolaGUI::initGUIComp()
{	
	//desc: da contur programului
	QHBoxLayout* layoutPrincipal = new QHBoxLayout;
	setLayout(layoutPrincipal);

	lstAnglia = new QListWidget;
	lstSpania = new QListWidget;
	rezultate = new QTableWidget(10, 4);
	rezultate->resizeRowsToContents();
	rezultate->resizeColumnsToContents();

	QVBoxLayout* mijlocLayout = new QVBoxLayout;
	QWidget* mijlocWidget = new QWidget;
	mijlocWidget->setLayout(mijlocLayout);
	
	btnGenereaza = new QPushButton("CHAMPIONS LEAGUE");
	mijlocLayout->addWidget(btnGenereaza);
	mijlocLayout->addWidget(rezultate);
	

	layoutPrincipal->addWidget(lstAnglia);
	layoutPrincipal->addWidget(mijlocWidget);
	layoutPrincipal->addWidget(lstSpania);
}

void ConsolaGUI::initGUISemnals()
{
	//da semnale
	QObject::connect(btnGenereaza, &QPushButton::clicked, [&]() {
		int contor = 0;
		auto solved = serv.rezolvaCampionat();

		for (int i = 0; i <= 8; i++) {
			if (i == 4 || i == 7) {
				continue;
			}
			for (int j = 0; j < 4; j++) {
				QTableWidgetItem* item = new QTableWidgetItem;
				item->setText(QString::fromStdString(solved[contor++]));
				rezultate->setItem(i, j, item);
			}

		}
		rezultate->resizeRowsToContents();
		rezultate->resizeColumnsToContents();
		
		/*
		auto listSpania = serv.getSpania();
		auto listAnglia = serv.getAnglia();

		std::srand(unsigned(std::time(0)));
		std::random_shuffle(listAnglia.begin(), listAnglia.end());
		std::random_shuffle(listSpania.begin(), listSpania.end());

		Echipa winner[5];

		for (int i = 0; i < 4; i++) {
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setText(QString::fromStdString(listAnglia[i].getNume()));
			rezultate->setItem(i, 0, item);
		}

		for (int i = 0; i < 4; i++) {
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setText(QString::fromStdString(listSpania[i].getNume()));
			rezultate->setItem(i, 3, item);
		}

		for (int i = 0; i < 4; i++) {
			auto scor = serv.solveMeci(listAnglia[i], listSpania[i]);
			QTableWidgetItem* item1 = new QTableWidgetItem;
			QTableWidgetItem* item2 = new QTableWidgetItem;
			item1->setText(QString::number(scor.first));
			item2->setText(QString::number(scor.second));

			if (scor.first >= scor.second)
				winner[i] = listAnglia[i];
			else
				winner[i] = listSpania[i];

			rezultate->setItem(i, 1, item1);
			rezultate->setItem(i, 2, item2);
		}

		for (int i = 0; i < 2; i++) {
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setText(QString::fromStdString(winner[i].getNume()));
			rezultate->setItem(i + 5, 0, item);
		}

		for (int i = 2; i < 4; i++) {
			QTableWidgetItem* item = new QTableWidgetItem;
			item->setText(QString::fromStdString(winner[i].getNume()));
			rezultate->setItem(i + 5 - 2, 3, item);
		}

		Echipa ewinner[2];
		for (int i = 0; i < 2; i++) {
			auto scoru = serv.solveMeci(winner[i], winner[i+2]);
			QTableWidgetItem* item1 = new QTableWidgetItem;
			QTableWidgetItem* item2 = new QTableWidgetItem;
			item1->setText(QString::number(scoru.first));
			item2->setText(QString::number(scoru.second));

			if (scoru.first >= scoru.second)
				ewinner[i] = winner[i];
			else
				ewinner[i] = winner[i + 2];

			rezultate->setItem(i + 5, 1, item1);
			rezultate->setItem(i + 5, 2, item2);
		}

		QTableWidgetItem* itemFi1 = new QTableWidgetItem;
		itemFi1->setText(QString::fromStdString(ewinner[0].getNume()));
		rezultate->setItem(8, 0, itemFi1);

		QTableWidgetItem* itemFi2 = new QTableWidgetItem;
		itemFi2->setText(QString::fromStdString(ewinner[1].getNume()));
		rezultate->setItem(8, 3, itemFi2);


		auto scorel = serv.solveMeci(ewinner[0], ewinner[1]);
		QTableWidgetItem* itemo1 = new QTableWidgetItem;
		QTableWidgetItem* itemo2 = new QTableWidgetItem;
		itemo1->setText(QString::number(scorel.first));
		itemo2->setText(QString::number(scorel.second));

		Echipa zaWinner;
		if (scorel.first >= scorel.second)
			zaWinner = ewinner[0];
		else
			zaWinner = ewinner[1];

		rezultate->setItem(8, 1, itemo1);
		rezultate->setItem(8, 2, itemo2);

		*/
	});

}

void ConsolaGUI::reloadLists(vector<Echipa>& list) {
	//desc: incarca lista pe care o primeste pe ecran
	lstAnglia->clear();
	lstSpania->clear();

	string max_atac = serv.getMaxAtac();
	string max_mij = serv.getMaxMij();
	string max_ap = serv.getMaxAp();

	for (auto it : list) {
		QListWidgetItem* item = new QListWidgetItem;
		if (it.getTara() == "Spania"){
			item->setText(QString::fromStdString(it.getNume()));
			if (it.getNume() == max_atac)
				item->setBackgroundColor(Qt::red);
			if (it.getNume() == max_ap)
				item->setBackgroundColor(Qt::yellow);
			if (it.getNume() == max_mij)
				item->setBackgroundColor(Qt::blue);
			lstSpania->addItem(item);
		}
		else {
			item->setText(QString::fromStdString(it.getNume()));
			if (it.getNume() == max_atac)
				item->setBackgroundColor(Qt::red);
			if (it.getNume() == max_ap)
				item->setBackgroundColor(Qt::yellow);
			if (it.getNume() == max_mij)
				item->setBackgroundColor(Qt::blue);
			lstAnglia->addItem(item);
		}


	}
}
