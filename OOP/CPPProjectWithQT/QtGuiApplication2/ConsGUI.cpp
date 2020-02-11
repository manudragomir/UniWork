#include "ConsGUI.h"
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <string>

void ConsGUI::initGUIComp()
{
	auto lyt = new QVBoxLayout();
	setLayout(lyt);

	auto lytSus = new QHBoxLayout();
	auto widSus = new QWidget;
	widSus->setLayout(lytSus);
	lytSus->addWidget(tbl);
	lytSus->addWidget(btnAdd);
	lytSus->addWidget(filtr);

	auto lytJos = new QFormLayout();
	auto widJos = new QWidget;
	widJos->setLayout(lytJos);
	lytJos->addRow("id", txtId);
	lytJos->addRow("desc",txtDesc);
	lytJos->addRow("stare",txtStare);
	lytJos->addRow("progrs",txtProgr);

	lyt->addWidget(widSus);
	lyt->addWidget(widJos);
}

void ConsGUI::initSemnals()
{
	QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
		int id = txtId->text().toInt();
		string desc = txtDesc->text().toStdString();
		string stare = txtStare->text().toStdString();
		auto pro = txtProgr->text().split(" ");
		int cnt = pro[0].toInt();
		vector < string > progrs;
		for (int i = 1; i <= cnt; i++) {
			progrs.push_back(pro[i].toStdString());
		}
		try {
			ctrl.add(id, desc, stare, progrs);
			reloadList(ctrl.getAll());
		}
		catch(MyException& ex){
			QMessageBox* msm = new QMessageBox;
			msm->setText(QString::fromStdString(ex.getMesaj()));
			msm->show();
		}
	});

	QObject::connect(filtr, &QLineEdit::textChanged, [&](){
		auto txt = filtr->text();
		if (txt.size() == 0) {
			reloadList(ctrl.getAll());
		}
		else {
			reloadList(ctrl.filter(txt.toStdString()));
		}
	});

}

void ConsGUI::reloadList(const vector<Task>& v)
{
	auto list = v;
	std::sort(list.begin(), list.end(), [](const Task& t1, const Task& t2) {return t1.getStare()<t2.getStare(); });
	tbl->setColumnCount(4);
	tbl->setRowCount(list.size());
	int row = 0;
	for (const auto& el : list) {
		QTableWidgetItem* itm1 = new QTableWidgetItem;
		QTableWidgetItem* itm2 = new QTableWidgetItem;
		QTableWidgetItem* itm3 = new QTableWidgetItem;
		QTableWidgetItem* itm4 = new QTableWidgetItem;
		itm1->setText(QString::fromStdString(std::to_string(el.getId())));
		itm2->setText(QString::fromStdString(el.getDesc()));
		itm3->setText(QString::fromStdString(el.getStare()));
		string s = "";
		for (const auto& elem : el.getProgrs()) {
			s = s + elem + " ";
		}
		itm4->setText(QString::fromStdString(s));
		tbl->setItem(row, 0, itm1);
		tbl->setItem(row, 1, itm2);
		tbl->setItem(row, 2, itm3);
		tbl->setItem(row, 3, itm4);
		row++;
	}
	tbl->resizeColumnsToContents();
	tbl->setMinimumSize(400, 400);
}
