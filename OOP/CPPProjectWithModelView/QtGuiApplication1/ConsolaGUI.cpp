#include "ConsolaGUI.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include <qlistwidget.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include "ModelList.h"

void ConsolaGUI::initGUIComp()
{
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	QWidget* widStanga = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widStanga->setLayout(vl);
	lst = new QListWidget;
	//vl->addWidget(lst);
	vl->addWidget(lstView);
	vl->addWidget(btnUndo);
	ly->addWidget(widStanga);

	QWidget* widDetalii = new QWidget;
	QFormLayout* formDetalii = new QFormLayout;
	widDetalii->setLayout(formDetalii);

	txtMaterie = new QLineEdit;
	formDetalii->addRow(new QLabel("Materie:"), txtMaterie);
	txtNrOre = new QLineEdit;
	formDetalii->addRow(new QLabel("NrOre:"), txtNrOre);
	txtTip = new QLineEdit;
	formDetalii->addRow(new QLabel("Tip:"), txtTip);
	txtCadruDidactic = new QLineEdit;
	formDetalii->addRow(new QLabel("Cadru didactic:"), txtCadruDidactic);

	QWidget* butoane = new QWidget;
	QHBoxLayout* ho = new QHBoxLayout;
	butoane->setLayout(ho);
	btnAdauga = new QPushButton("Adauga materie");

	btnAdauga->setStyleSheet("width:200px;");
	ho->addWidget(btnAdauga);
	ho->addWidget(btnSterge);
	ho->addWidget(btnModifica);
	formDetalii->addWidget(butoane);

	QWidget* alteButoane = new QWidget;
	QHBoxLayout* hob = new QHBoxLayout;
	alteButoane->setLayout(hob);
	hob->addWidget(btnFilter);

	QWidget* sortButons = new QWidget;
	QHBoxLayout* hob1 = new QHBoxLayout;
	sortButons->setLayout(hob1);
	hob1->addWidget(btnSortByOre);
	hob1->addWidget(btnSortByDenumire);
	hob1->addWidget(btnSortByCd);


	formDetalii->addWidget(sortButons);
	formDetalii->addWidget(alteButoane);
	formDetalii->addWidget(btnCon);
	formDetalii->addWidget(btnDesen);

	QHBoxLayout* lowLayout = new QHBoxLayout;
	QWidget* lowWidget = new QWidget;
	lowWidget->setLayout(lowLayout);
	lowLayout->addWidget(label);
	nrElemCos->setText("0");
	lowLayout->addWidget(nrElemCos);

	ly->addWidget(widDetalii);
	ly->addWidget(lowWidget);

}

void ConsolaGUI::initGUISemnals()
{
	QObject::connect(lstView->selectionModel(), &QItemSelectionModel::clearSelection, [&]() {
		if (lstView->selectionModel()->selectedIndexes().isEmpty()) {
			qDebug() << "EMPTY" << "\n";
			txtMaterie->setText("");
			txtNrOre->setText("");
			txtCadruDidactic->setText("");
			txtTip->setText("");
			return;
		}
	});
	QObject::connect(lstView->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lstView->selectionModel()->selectedIndexes().isEmpty()) {
			qDebug() << "EMPTY" << "\n";
			txtMaterie->setText("");
			txtNrOre->setText("");
			txtCadruDidactic->setText("");
			txtTip->setText("");
			return;
		}
		/*auto vec = service.getAllElements();
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		string txt = selItem->text().toStdString();
		Disciplina dis;*/
		auto vec = service.getAllElements();
		auto selIndex = lstView->selectionModel()->selectedIndexes().at(0);
		QString txt = selIndex.data(Qt::DisplayRole).toString();
		qDebug() << txt << "\n";
		Disciplina dis;
		for (auto d : vec)
			if (d.get_denumire() == txt.toStdString())
				dis = d;
		txtMaterie->setText(QString::fromStdString(dis.get_denumire()));
		txtCadruDidactic->setText(QString::fromStdString(dis.get_cadru_didactic()));
		txtNrOre->setText(QString::number(dis.get_ore()));
		txtTip->setText(QString::fromStdString(dis.get_tip()));
	});
	/*
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		if (lst->selectedItems().isEmpty()) {
			txtMaterie->setText("");
			txtNrOre->setText("");
			txtCadruDidactic->setText("");
			txtTip->setText("");
			return;
		}
		auto vec = service.getAllElements();
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		string txt = selItem->text().toStdString();
		Disciplina dis;
		for (auto d : vec)
			if (d.get_denumire() == txt)
				dis = d;
		txtMaterie->setText(QString::fromStdString(dis.get_denumire()));
		txtCadruDidactic -> setText(QString::fromStdString(dis.get_cadru_didactic()));
		txtNrOre->setText(QString::number(dis.get_ore()));
		txtTip->setText(QString::fromStdString(dis.get_tip()));
	});*/

	QObject::connect(btnAdauga, &QPushButton::clicked, this, &ConsolaGUI::add);
	QObject::connect(btnSterge, &QPushButton::clicked, this, &ConsolaGUI::sterge);
	QObject::connect(btnModifica, &QPushButton::clicked, this, &ConsolaGUI::modify);
	QObject::connect(btnFilter, &QPushButton::clicked, this, &ConsolaGUI::filter);

	///cum dau parametri?
	QObject::connect(btnSortByDenumire, &QPushButton::clicked, this, &ConsolaGUI::sort2);
	QObject::connect(btnSortByOre, &QPushButton::clicked, this, &ConsolaGUI::sort1);
	QObject::connect(btnSortByCd, &QPushButton::clicked, this, &ConsolaGUI::sort3);

	QObject::connect(btnUndo, &QPushButton::clicked, this, &ConsolaGUI::undo);
	QObject::connect(btnCon, &QPushButton::clicked, this, &ConsolaGUI::contract);


	QObject::connect(btnDesen, &QPushButton::clicked, this, &ConsolaGUI::desen);
}

void ConsolaGUI::desen() {
	CosReadOnlyGUI* desenGUI = new CosReadOnlyGUI{ service };
	desenGUI->show();
}

void ConsolaGUI::reloadList(const std::vector<Disciplina>& disci)
{
	/*
	lst->clear();
	for (const auto&d : disci)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(d.get_denumire()), lst);
	}
	*/
	model->setDisci(disci);
}


void ConsolaGUI::add()
{
	try {
		service.add(txtMaterie->text().toStdString(), stoi(txtNrOre->text().toStdString()), txtTip->text().toStdString(), txtCadruDidactic->text().toStdString());
		reloadList(service.getAllElements());
	}
	catch (RepoExc& ex) {
		QMessageBox::warning(this, "WARNING", QString::fromStdString(ex.getMsg()));
	}
}

void ConsolaGUI::contract()
{
	ContractGUI* cgui = new ContractGUI(service);
	cgui->show();
}

void ConsolaGUI::modify()
{
	try {
		service.modify(txtMaterie->text().toStdString(), stoi(txtNrOre->text().toStdString()), txtTip->text().toStdString(), txtCadruDidactic->text().toStdString());
		reloadList(service.getAllElements());
	}
	catch (RepoExc& ex) {
		QMessageBox::warning(this, "WARNING", QString::fromStdString(ex.getMsg()));
	}
}

class FilterWindow : public QWidget
{
private:
	GRASPController& serv;
	QPushButton* btnOre = new QPushButton("Dupa ore");
	QPushButton* btnCd = new QPushButton("Dupa cadru didactic");

	QListWidget* lst = new QListWidget;
	void InitFilter() {

		QVBoxLayout* hl = new QVBoxLayout;
		this->setLayout(hl);

		QHBoxLayout* hl1 = new QHBoxLayout;
		QWidget* butoane = new QWidget;
		butoane->setLayout(hl1);
		hl1->addWidget(btnOre);
		hl1->addWidget(btnCd);
		
		QVBoxLayout* hl2 = new QVBoxLayout;
		QWidget* list = new QWidget;
		list->setLayout(hl2);

		hl2->addWidget(lst);

		hl->addWidget(butoane);
		hl->addWidget(list);
	}

	void InitFilterSemnals() {
		QObject::connect(btnOre, &QPushButton::clicked, [&]() {
			bool ok;
			int val = QInputDialog::getInt(this, "Alegere", "Alege nr ore", 0, 0,
											100, 10, &ok);

			ReloadList(serv.filterOre(val));
		});

		QObject::connect(btnCd, &QPushButton::clicked, [&]() {
			bool ok;
			string Cd = QInputDialog::getText(this, "QInputDialog::getText()",
				"User name:", QLineEdit::Normal, "da", &ok).toStdString();

			ReloadList(serv.filterCd(Cd));
		});


	}

	void ReloadList(vector <Disciplina>& v) {
		lst->clear();
		int index = 0;
		for (auto it : v)
		{
			QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(it.get_denumire()));
			if (index % 2 == 0)
				item->setBackgroundColor(Qt::magenta);
			else
				item->setBackgroundColor(Qt::darkCyan);

			++index;
			lst->addItem(item);
		}
	}

public:
	FilterWindow(GRASPController& serv) : serv{ serv } {
		InitFilter();
		InitFilterSemnals();
	};
};

void ConsolaGUI::filter()
{
	FilterWindow* w = new FilterWindow{ service };
	w->setObjectName("Fereastra de filtrare");
	w->setWindowModality(Qt::ApplicationModal);
	w->show();
}

void ConsolaGUI::sterge()
{
	try {
		service.deletee(txtMaterie->text().toStdString());
		reloadList(service.getAllElements());
	}
	catch (RepoExc& ex) {
		QMessageBox::warning(this, "WARNING", QString::fromStdString(ex.getMsg()));
	}
}

void ConsolaGUI::sort1()
{
	auto list = service.sorting(1);
	reloadList(list);
}

void ConsolaGUI::sort2()
{
	auto list = service.sorting(2);
	reloadList(list);
}

void ConsolaGUI::sort3()
{
	auto list = service.sorting(3);
	reloadList(list);
}

void ConsolaGUI::undo()
{
	try {
		service.undo();
		reloadList(service.getAllElements());
	}
	catch (DisciplinaExc& ex)
	{
		QMessageBox* ms = new QMessageBox;
		ms->setText("Nu se mai poate da undo!");
		ms->show();
	}
}


