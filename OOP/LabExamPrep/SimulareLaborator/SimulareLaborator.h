#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulareLaborator.h"

class SimulareLaborator : public QMainWindow
{
	Q_OBJECT

public:
	SimulareLaborator(QWidget *parent = Q_NULLPTR);

private:
	Ui::SimulareLaboratorClass ui;
};
