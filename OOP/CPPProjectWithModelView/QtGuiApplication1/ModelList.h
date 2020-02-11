#pragma once
#include<QAbstractListModel>
#include "Disciplina.h"
#include <vector>
#include <qdebug.h>
class MyListModel :public QAbstractListModel {
	std::vector<Disciplina> disci;
public:
	MyListModel(const std::vector<Disciplina>& disci) :disci{ disci } {
	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		return disci.size();
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			auto sp = disci[index.row()].get_denumire();
			return QString::fromStdString(sp);
		}
		return QVariant{};
	}

	void setDisci(const vector<Disciplina>& disci) {
		this->disci = disci;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(disci.size(), 1);
		emit dataChanged(topLeft, bottomR);
	}
};