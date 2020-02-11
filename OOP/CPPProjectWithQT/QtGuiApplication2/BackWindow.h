#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include "Ctrl.h"
#include <string>

using std::string;

class BackWindow : public QWidget, public Observer
{
private:
	QListWidget* lst = new QListWidget;
	string stare;
	Ctrl& ctrl;

	QPushButton* btnOpen = new QPushButton{ "open" };
	QPushButton* btnClosed = new QPushButton{ "closed" };
	QPushButton* btnInProgress = new QPushButton{ "inprogess" };

	void initGUI() {
		auto box = new QHBoxLayout;
		setLayout(box);

		box->addWidget(lst);
		box->addWidget(btnOpen);
		box->addWidget(btnClosed);
		box->addWidget(btnInProgress);
	}
	void initSemnals() {
		QObject::connect(btnOpen, &QPushButton::clicked, [&]() {
			if (lst->selectedItems().isEmpty() == false) {
				auto item = lst->selectedItems().at(0);
				int id = item->text().toInt();
				ctrl.changeState(id, "open");
			}
		});
		QObject::connect(btnClosed, &QPushButton::clicked, [&]() {
			if (lst->selectedItems().isEmpty() == false) {
				auto item = lst->selectedItems().at(0);
				int id = item->text().toInt();
				ctrl.changeState(id, "closed");
			}
		});

		QObject::connect(btnInProgress, &QPushButton::clicked, [&]() {
			if (lst->selectedItems().isEmpty() == false) {
				auto item = lst->selectedItems().at(0);
				int id = item->text().toInt();
				ctrl.changeState(id, "inprogress");
			}});
	};
	void reloadList() {
		lst->clear();
		auto list = ctrl.getStare(stare);
		for (const auto& el : list) {
			QListWidgetItem* it = new QListWidgetItem;
			it->setText(QString::fromStdString(std::to_string(el.getId())));
			lst->addItem(it);
		}
	}
public:
	BackWindow(string st, Ctrl& ctrl) : stare{ st }, ctrl{ ctrl } {
		ctrl.addObserver(this);
		this->setWindowTitle(QString::fromStdString(st));
		initGUI();
		initSemnals();
		reloadList();
	};
	void update() override {
		reloadList();
	}
	~BackWindow() {};
};
